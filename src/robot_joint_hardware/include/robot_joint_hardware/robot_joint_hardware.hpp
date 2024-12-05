#ifndef ROBOT_JOINT_HARDWARE__DIFFBOT_SYSTEM_HPP_
#define ROBOT_JOINT_HARDWARE__DIFFBOT_SYSTEM_HPP_

#include <memory>
#include <string>
#include <vector>

#include "hardware_interface/base_interface.hpp"
#include "hardware_interface/handle.hpp"
#include "hardware_interface/hardware_info.hpp"
#include "hardware_interface/system_interface.hpp"
#include "hardware_interface/types/hardware_interface_return_values.hpp"
#include "hardware_interface/types/hardware_interface_status_values.hpp"
#include "rclcpp/macros.hpp"
#include "robot_joint_hardware/visibility_control.h"


namespace robot_joint_hardware
{
class RobotJointHardware
: public hardware_interface::BaseInterface<hardware_interface::SystemInterface>
{
public:
  RCLCPP_SHARED_PTR_DEFINITIONS(RobotJointHardware);

  ROBOT_JOINT_HARDWARE_PUBLIC
  hardware_interface::return_type configure(const hardware_interface::HardwareInfo & info) override;

  ROBOT_JOINT_HARDWARE_PUBLIC
  std::vector<hardware_interface::StateInterface> export_state_interfaces() override;

  ROBOT_JOINT_HARDWARE_PUBLIC
  std::vector<hardware_interface::CommandInterface> export_command_interfaces() override;

  ROBOT_JOINT_HARDWARE_PUBLIC
  hardware_interface::return_type start() override;

  ROBOT_JOINT_HARDWARE_PUBLIC
  hardware_interface::return_type stop() override;

  ROBOT_JOINT_HARDWARE_PUBLIC
  hardware_interface::return_type read() override;

  ROBOT_JOINT_HARDWARE_PUBLIC
  hardware_interface::return_type write() override;

private:

  // Parameters for the DiffBot simulation
  double hw_start_sec_; // TODO：暂时可能用不到
  double hw_stop_sec_;  // TODO：暂时可能用不到

  // Store the command for the simulated robot
  std::vector<double> hw_commands_effort;
  std::vector<double> hw_commands_position_;
  std::vector<double> hw_commands_velocitie_;
  std::vector<double> hw_commands_effort_;

//   // Store the wheeled robot position
//   double base_x_, base_y_, base_theta_;
};

}  // namespace ROBOT_JOINT_HARDWARE



#endif  