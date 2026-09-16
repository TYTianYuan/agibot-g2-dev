#include "options.h"

#include <cerrno>
#include <cmath>
#include <cstdlib>

namespace example {
namespace {

const JointLimit* FindJoint(const std::string& name) {
  for (const auto& joint : JointLimits()) {
    if (name == joint.name) return &joint;
  }
  return nullptr;
}

bool Number(const std::string& text, double* value) {
  char* end = nullptr;
  errno = 0;
  *value = std::strtod(text.c_str(), &end);
  return end != text.c_str() && *end == '\0' && errno != ERANGE &&
         std::isfinite(*value);
}

}  // namespace

const std::vector<JointLimit>& JointLimits() {
  static const std::vector<JointLimit> limits = {
      {"idx01_body_joint1", -1.082104, 0.000174},
      {"idx02_body_joint2", -0.000174, 2.652900},
      {"idx03_body_joint3", -1.919862, 1.570970},
      {"idx04_body_joint4", -0.436332, 0.436332},
      {"idx05_body_joint5", -3.045599, 3.045599},
      {"idx11_head_joint1", -1.570970, 1.570970},
      {"idx12_head_joint2", -0.349240, 0.349240},
      {"idx13_head_joint3", -0.534773, 0.534773},
      {"idx21_arm_l_joint1", -3.071796, 3.071796},
      {"idx22_arm_l_joint2", -2.059505, 2.059505},
      {"idx23_arm_l_joint3", -3.071796, 3.071796},
      {"idx24_arm_l_joint4", -2.495838, 1.012308},
      {"idx25_arm_l_joint5", -3.071796, 3.071796},
      {"idx26_arm_l_joint6", -1.012308, 1.012308},
      {"idx27_arm_l_joint7", -1.535907, 1.535907},
      {"idx61_arm_r_joint1", -3.071796, 3.071796},
      {"idx62_arm_r_joint2", -2.059505, 2.059505},
      {"idx63_arm_r_joint3", -3.071796, 3.071796},
      {"idx64_arm_r_joint4", -2.495838, 1.012308},
      {"idx65_arm_r_joint5", -3.071796, 3.071796},
      {"idx66_arm_r_joint6", -1.012308, 1.012308},
      {"idx67_arm_r_joint7", -1.535907, 1.535907},
  };
  return limits;
}

bool Parse(const std::vector<std::string>& args, Options* options,
           std::string* error) {
  *options = Options{};
  if (args.empty() || (args.size() == 1 && args[0] == "state")) return true;
  if (args.size() == 1 && (args[0] == "--help" || args[0] == "help")) {
    options->command = Command::kHelp;
    return true;
  }
  if ((args[0] == "joint" || args[0] == "nudge") &&
      (args.size() == 3 || args.size() == 4)) {
    options->command = args[0] == "joint" ? Command::kJoint : Command::kNudge;
    options->joint = args[1];
    const auto* limit = FindJoint(options->joint);
    if (!limit) {
      *error = "Unknown upper-body joint. See --help for supported names.";
      return false;
    }
    if (!Number(args[2], &options->position) ||
        (args.size() == 4 && !Number(args[3], &options->speed)) ||
        options->speed <= 0.0) {
      *error = "Position/delta must be finite; speed must be finite and positive.";
      return false;
    }
    if (options->command == Command::kJoint &&
        (options->position < limit->min || options->position > limit->max)) {
      *error = "Target is outside the documented joint limits.";
      return false;
    }
    return true;
  }
  if (args[0] == "gripper" && (args.size() == 3 || args.size() == 4)) {
    options->command = Command::kGripper;
    if (args[1] != "left" && args[1] != "right") {
      *error = "Gripper side must be left or right.";
      return false;
    }
    options->group = args[1] + "_tool";
    options->gripper_type = args.size() == 4 ? args[2] : "auto";
    options->gripper_action = args.back();
    if (options->gripper_action != "open" && options->gripper_action != "close") {
      *error = "Gripper action must be open or close.";
      return false;
    }
    if (options->gripper_type != "auto" &&
        !GripperPosition(options->gripper_type, options->gripper_action,
                         &options->position)) {
      *error = "Gripper type must be auto, omnipicker, dahuan or ctek90d.";
      return false;
    }
    return true;
  }
  *error = "Invalid command or argument count. See --help.";
  return false;
}

bool GripperPosition(const std::string& type, const std::string& action,
                     double* position) {
  if (action != "open" && action != "close") return false;
  if (type == "omnipicker") {
    *position = action == "open" ? -0.785 : 0.0;
  } else if (type == "dahuan") {
    *position = action == "open" ? 0.0 : 0.025;
  } else if (type == "ctek90d") {
    *position = action == "open" ? -0.91 : 0.0;
  } else {
    return false;
  }
  return true;
}

bool PlanJoint(const Options& options, double current, double* target,
               double* lifetime, std::string* error) {
  const auto* limit = FindJoint(options.joint);
  if (!limit || !std::isfinite(current) || current < limit->min ||
      current > limit->max) {
    *error = "Current motor position is invalid or outside documented limits.";
    return false;
  }
  *target = options.command == Command::kNudge
                ? current + options.position
                : options.position;
  if (!std::isfinite(*target) || *target < limit->min || *target > limit->max) {
    *error = "Target is outside the documented joint limits; no command sent.";
    return false;
  }
  // Allow planning overhead in addition to travel time at the requested speed.
  *lifetime = 5.0 + 2.0 * std::abs(*target - current) / options.speed;
  if (!std::isfinite(*lifetime)) {
    *error = "Requested motion duration is not representable.";
    return false;
  }
  return true;
}

const char* Usage() {
  return R"(Usage:
  example [state]
  example joint JOINT POSITION_RAD [SPEED_RAD_PER_SEC]
  example nudge JOINT DELTA_RAD [SPEED_RAD_PER_SEC]
  example gripper left|right [auto|omnipicker|dahuan|ctek90d] open|close
  example --help

No arguments: read state only. Default joint speed: 0.1 rad/s.
joint/nudge send one blocking planned motion for the named joint.
gripper reads the installed model by default, then calls MoveEEPos.
Only issue motion commands with the robot clear and its emergency stop accessible.
)";
}

}  // namespace example
