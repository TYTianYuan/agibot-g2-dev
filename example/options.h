#pragma once

#include <string>
#include <vector>

namespace example {

enum class Command { kHelp, kState, kJoint, kNudge, kGripper };

struct JointLimit {
  const char* name;
  double min;
  double max;
};

struct Options {
  Command command = Command::kState;
  std::string joint;
  double position = 0.0;
  double speed = 0.1;
  std::string group;
  std::string gripper_type;
  std::string gripper_action;
};

const std::vector<JointLimit>& JointLimits();
bool Parse(const std::vector<std::string>& args, Options* options,
           std::string* error);
bool PlanJoint(const Options& options, double current, double* target,
               double* lifetime, std::string* error);
bool GripperPosition(const std::string& type, const std::string& action,
                     double* position);
const char* Usage();

}  // namespace example
