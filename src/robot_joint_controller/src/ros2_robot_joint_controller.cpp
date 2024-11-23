#include "robot_joint_controller.hpp"
#include <hardware_interface/types/hardware_interface_type_values.hpp>

namespace robot_joint_controller
{

RobotJointController::RobotJointController() : ControllerInterface() {}

controller_interface::return_type RobotJointController::init(const std::string &controller_name)
{
  auto ret = ControllerInterface::init(controller_name);
  if (ret != controller_interface::return_type::OK)
  {
    return ret;
  }

  // Initialize state publisher
  state_publisher_ = std::make_shared<realtime_tools::RealtimePublisher<robot_msgs::msg::MotorState>>(get_node(), "/state", 10);

  return controller_interface::return_type::OK;
}

controller_interface::return_type RobotJointController::on_activate(const rclcpp_lifecycle::State & /*previous_state*/)
{
  // Get joint names and interfaces
  if (command_interfaces_.empty())
  {
    RCLCPP_ERROR(get_node()->get_logger(), "Command interfaces are empty");
    return controller_interface::return_type::ERROR;
  }

  // Use the first command interface (effort control)
  joint_command_interface_ = command_interfaces_[0];
  joint_name_ = joint_command_interface_.get_name();

  // Parse URDF
  urdf::Model urdf;
  if (!urdf.initParam("robot_description"))
  {
    RCLCPP_ERROR(get_node()->get_logger(), "Failed to parse URDF");
    return controller_interface::return_type::ERROR;
  }
  joint_urdf_ = urdf.getJoint(joint_name_);
  if (!joint_urdf_)
  {
    RCLCPP_ERROR(get_node()->get_logger(), "Joint '%s' not found in URDF", joint_name_.c_str());
    return controller_interface::return_type::ERROR;
  }

  // Subscribe to command topic
  command_subscriber_ = get_node()->create_subscription<robot_msgs::msg::MotorCommand>(
      "/command", 10, std::bind(&RobotJointController::command_callback, this, std::placeholders::_1));

  return controller_interface::return_type::OK;
}

controller_interface::return_type RobotJointController::on_deactivate(const rclcpp_lifecycle::State & /*previous_state*/)
{
  command_subscriber_.reset();
  state_publisher_.reset();
  return controller_interface::return_type::OK;
}

void RobotJointController::command_callback(const robot_msgs::msg::MotorCommand::SharedPtr msg)
{
  last_command_ = *msg;
}

controller_interface::return_type RobotJointController::update(const rclcpp::Time & /*time*/, const rclcpp::Duration &period)
{
  double current_position = joint_command_interface_.get_value();
  double current_velocity = (current_position - last_position_) / period.seconds();
  double current_effort = last_command_.kp * (last_command_.q - current_position) +
                          last_command_.kd * (last_command_.dq - current_velocity) +
                          last_command_.tau;

  effort_limits(current_effort);

  joint_command_interface_.set_value(current_effort);

  // Publish state
  if (state_publisher_ && state_publisher_->trylock())
  {
    state_publisher_->msg_.q = current_position;
    state_publisher_->msg_.dq = current_velocity;
    state_publisher_->msg_.tau_est = current_effort;
    state_publisher_->unlockAndPublish();
  }

  last_position_ = current_position;
  last_velocity_ = current_velocity;

  return controller_interface::return_type::OK;
}

void RobotJointController::position_limits(double &position)
{
  if (joint_urdf_->type == urdf::Joint::REVOLUTE || joint_urdf_->type == urdf::Joint::PRISMATIC)
  {
    clamp(position, joint_urdf_->limits->lower, joint_urdf_->limits->upper);
  }
}

void RobotJointController::velocity_limits(double &velocity)
{
  if (joint_urdf_->type == urdf::Joint::REVOLUTE || joint_urdf_->type == urdf::Joint::PRISMATIC)
  {
    clamp(velocity, -joint_urdf_->limits->velocity, joint_urdf_->limits->velocity);
  }
}

void RobotJointController::effort_limits(double &effort)
{
  if (joint_urdf_->type == urdf::Joint::REVOLUTE || joint_urdf_->type == urdf::Joint::PRISMATIC)
  {
    clamp(effort, -joint_urdf_->limits->effort, joint_urdf_->limits->effort);
  }
}

}  // namespace robot_joint_controller

#include "pluginlib/class_list_macros.hpp"
PLUGINLIB_EXPORT_CLASS(robot_joint_controller::RobotJointController, controller_interface::ControllerInterface)
