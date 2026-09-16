#include "options.h"

#include <algorithm>
#include <cctype>
#include <chrono>
#include <exception>
#include <iomanip>
#include <iostream>
#include <string>
#include <thread>
#include <vector>

#include "gdk/gdk.h"

namespace {

namespace gdk = agibot::gdk;

bool Check(gdk::GDKRes result, const char* operation) {
  if (result == gdk::GDKRes::kSuccess) return true;
  std::cerr << operation << " failed, GDK code=" << static_cast<int>(result)
            << '\n';
  return false;
}

bool ReadState(gdk::Robot& robot, gdk::JointStates* states) {
  if (!Check(robot.GetJointStates(*states), "GetJointStates")) return false;
  if (states->states.empty()) {
    std::cerr << "No joint feedback received. Check robot connection and GDK.\n";
    return false;
  }
  return true;
}

int Run(const example::Options& options) {
  gdk::Robot robot;
  std::this_thread::sleep_for(std::chrono::seconds(1));

  gdk::WholeBodyStatus body;
  if (!Check(robot.GetWholeBodyStatus(body), "GetWholeBodyStatus")) return 1;
  std::cout << "left_end_model=" << body.left_end_model
            << " right_end_model=" << body.right_end_model << '\n';

  if (options.command == example::Command::kGripper) {
    const bool left = options.group == "left_tool";
    if ((left ? body.left_end_error : body.right_end_error) != 0 ||
        (left ? body.left_arm_estop : body.right_arm_estop)) {
      std::cerr << "Selected tool has an error or arm is in emergency stop; "
                   "no command sent.\n";
      return 1;
    }
    std::string model = left ? body.left_end_model : body.right_end_model;
    std::transform(model.begin(), model.end(), model.begin(),
                   [](unsigned char c) { return std::tolower(c); });
    double position = 0.0;
    const bool known = example::GripperPosition(model, options.gripper_action,
                                               &position);
    if (options.gripper_type == "auto") {
      if (!known) {
        std::cerr << "Unrecognized reported model: '" << model
                  << "'. Verify the installed model before specifying its type.\n";
        return 1;
      }
    } else {
      if (known && options.gripper_type != model) {
        std::cerr << "Requested gripper type differs from reported model; "
                     "no command sent.\n";
        return 1;
      }
      model = options.gripper_type;
      position = options.position;
    }
    gdk::JointStates request;
    request.group = options.group;
    request.target_type = model;
    request.states.resize(1);
    request.nums = request.states.size();
    request.states[0].position = position;
    std::cout << "MoveEEPos: group=" << request.group
              << " type=" << request.target_type
              << " position=" << position << std::endl;
    if (!Check(robot.MoveEEPos(request), "MoveEEPos")) return 1;
    std::cout << "MoveEEPos returned success. Verify gripper movement on robot.\n";
    return 0;
  }

  gdk::JointStates states;
  if (!ReadState(robot, &states)) return 1;
  if (options.command == example::Command::kState) {
    std::cout << "left_arm_error=" << body.left_arm_error
              << " right_arm_error=" << body.right_arm_error
              << " left_arm_estop=" << body.left_arm_estop
              << " right_arm_estop=" << body.right_arm_estop
              << " left_end_error=" << body.left_end_error
              << " right_end_error=" << body.right_end_error << '\n';
    std::cout << "timestamp=" << states.timestamp
              << " received_joints=" << states.states.size() << '\n';
    for (const auto& state : states.states) {
      std::cout << state.name << " motor_position=" << state.motor_position
                << " motor_velocity=" << state.motor_velocity
                << " error_code=" << state.error_code << '\n';
    }
    return 0;
  }

  const bool left_arm = options.joint.find("_arm_l_") != std::string::npos;
  const bool right_arm = options.joint.find("_arm_r_") != std::string::npos;
  if ((left_arm && (body.left_arm_error != 0 || body.left_arm_estop)) ||
      (right_arm && (body.right_arm_error != 0 || body.right_arm_estop)) ||
      (options.joint.find("_head_") != std::string::npos && body.neck_error != 0) ||
      (options.joint.find("_body_") != std::string::npos &&
       (body.waist_error != 0 || body.lift_error != 0))) {
    std::cerr << "Selected joint group has an error or is in emergency stop; "
                 "no command sent.\n";
    return 1;
  }

  for (const auto& state : states.states) {
    if (state.name != options.joint) continue;
    if (state.error_code != 0) {
      std::cerr << "Joint has error_code=" << state.error_code
                << "; no command sent.\n";
      return 1;
    }
    double target = 0.0;
    double lifetime = 0.0;
    std::string error;
    if (!example::PlanJoint(options, state.motor_position, &target, &lifetime,
                            &error)) {
      std::cerr << error << '\n';
      return 1;
    }
    gdk::JointControlReq request;
    request.life_time = lifetime;
    request.joint_names = {options.joint};
    request.joint_positions = {target};
    request.joint_velocities = {options.speed};
    request.detail = "example upper-body joint motion";
    std::cout << "JointControl: " << options.joint
              << " current=" << state.motor_position << " target=" << target
              << " speed=" << options.speed << " rad/s, lifetime=" << lifetime
              << " s" << std::endl;
    if (!Check(robot.JointControl(request), "JointControl")) return 1;
    std::cout << "JointControl returned success.\n";
    gdk::JointStates after;
    if (!ReadState(robot, &after)) return 1;
    for (const auto& feedback : after.states) {
      if (feedback.name != options.joint) continue;
      std::cout << "Feedback: motor_position=" << feedback.motor_position
                << " target=" << target
                << " error_code=" << feedback.error_code << '\n';
      return feedback.error_code == 0 ? 0 : 1;
    }
    std::cerr << "Requested joint missing from post-motion feedback.\n";
    return 1;
  }
  std::cerr << "Requested joint missing from feedback; no command sent.\n";
  return 1;
}

}  // namespace

int main(int argc, char** argv) {
  example::Options options;
  std::string error;
  if (!example::Parse(std::vector<std::string>(argv + 1, argv + argc), &options,
                      &error)) {
    std::cerr << error << '\n' << example::Usage();
    return 2;
  }
  if (options.command == example::Command::kHelp) {
    std::cout << example::Usage() << "\nJoint limits (rad):\n";
    for (const auto& joint : example::JointLimits()) {
      std::cout << joint.name << " [" << joint.min << ", " << joint.max << "]\n";
    }
    return 0;
  }
  if (!Check(gdk::GDKInit(), "GDKInit")) return 1;
  std::cout << std::fixed << std::setprecision(6);
  int result = 1;
  try {
    result = Run(options);
  } catch (const std::exception& exception) {
    std::cerr << "Example failed: " << exception.what() << '\n';
  }
  if (!Check(gdk::GDKRelease(), "GDKRelease")) result = 1;
  return result;
}
