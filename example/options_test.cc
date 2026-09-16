#include "options.h"

#include <cmath>
#include <iostream>
#include <limits>
#include <string>
#include <vector>

int main() {
  int failures = 0;
  auto check = [&](bool ok, const std::string& message) {
    if (!ok) {
      std::cerr << "FAIL: " << message << '\n';
      ++failures;
    }
  };
  example::Options options;
  std::string error;
  check(example::Parse({}, &options, &error) &&
            options.command == example::Command::kState,
        "default command only reads state");
  check(example::Parse({"gripper", "left", "open"}, &options, &error) &&
            options.gripper_type == "auto" && options.gripper_action == "open",
        "default gripper command uses reported model");
  double unknown_position = 0;
  check(!example::GripperPosition("", "open", &unknown_position) &&
            !example::GripperPosition("o10_t2", "open", &unknown_position),
        "empty model or dexterous hand must not use a guessed gripper mapping");
  for (const auto& joint : example::JointLimits()) {
    check(example::Parse({"joint", joint.name, "0"}, &options, &error),
          std::string("supported joint: ") + joint.name);
  }
  const std::vector<std::vector<std::string>> invalid = {
      {"state", "extra"}, {"joint"}, {"nudge", "unknown", "0.1"},
      {"joint", "idx21_arm_l_joint1", "nan"},
      {"joint", "idx21_arm_l_joint1", "inf"},
      {"joint", "idx21_arm_l_joint1", "0.1junk"},
      {"joint", "idx21_arm_l_joint1", ""},
      {"joint", "idx21_arm_l_joint1", "4"},
      {"joint", "idx21_arm_l_joint1", "0", "0"},
      {"joint", "idx21_arm_l_joint1", "0", "-0.1"},
      {"joint", "idx21_arm_l_joint1", "0", "nan"},
      {"gripper", "both", "dahuan", "open"},
      {"gripper", "left", "unknown", "open"},
      {"gripper", "left", "dahuan", "toggle"}};
  for (const auto& args : invalid) {
    check(!example::Parse(args, &options, &error), "reject invalid command");
  }
  struct Gripper { const char* type; double open; double close; };
  for (const auto& gripper : std::vector<Gripper>{
           {"omnipicker", -0.785, 0}, {"dahuan", 0, 0.025},
           {"ctek90d", -0.91, 0}}) {
    for (const std::string side : {"left", "right"}) {
      for (const std::string action : {"open", "close"}) {
        check(example::Parse({"gripper", side, gripper.type, action}, &options,
                             &error), "parse gripper");
        check(options.group == side + "_tool", "select correct tool group");
        check(options.position == (action == "open" ? gripper.open : gripper.close),
              "map open/close according to GDK v2.6.3");
      }
    }
  }
  check(example::Parse({"nudge", "idx24_arm_l_joint4", "0.05"}, &options,
                       &error), "parse relative movement");
  double target = 0;
  double lifetime = 0;
  check(example::PlanJoint(options, -0.5, &target, &lifetime, &error) &&
            std::abs(target + 0.45) < 1e-12 && lifetime > 0.5,
        "relative movement uses measured position and allows travel time");
  check(!example::PlanJoint(options, 1.0, &target, &lifetime, &error),
        "reject relative target past asymmetric elbow limit");
  check(!example::PlanJoint(options, std::numeric_limits<double>::quiet_NaN(),
                            &target, &lifetime, &error), "reject invalid feedback");
  check(!example::PlanJoint(options, -3, &target, &lifetime, &error),
        "reject feedback outside joint limits");
  std::cout << "Failures: " << failures << '\n';
  return failures == 0 ? 0 : 1;
}
