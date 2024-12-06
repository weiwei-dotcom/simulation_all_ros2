#ifndef ROBOT_JOINT_CONTROLLER_HPP
#define ROBOT_JOINT_CONTROLLER_HPP

#include <urdf/model.h>
#include "rclcpp/qos.hpp"
#include "realtime_tools/realtime_publisher.h"
#include "hardware_interface/loaned_command_interface.hpp"
#include "hardware_interface/loaned_state_interface.hpp"
#include "controller_interface/controller_interface.hpp"
#include "hardware_interface/types/hardware_interface_type_values.hpp"
#include "realtime_tools/realtime_buffer.h"
#include "realtime_tools/realtime_publisher.h"
#include "rclcpp_lifecycle/state.hpp"
#include "rclcpp_lifecycle/node_interfaces/lifecycle_node_interface.hpp"
#include "visibility_control.h"
#include <rclcpp/rclcpp.hpp>

#include <std_msgs/msg/float64.h>
#include "robot_msgs/msg/motor_command.hpp"
#include "robot_msgs/msg/motor_state.hpp"
#include <geometry_msgs/msg/wrench_stamped.hpp>
#include <stdio.h>
#include <stdint.h>
#include <algorithm>
#include <math.h>
#include <cstring>
#include <string.h>
#include <utility>

#define PosStopF  (2.146E+9f)
#define VelStopF  (16000.0f)


namespace robot_joint_controller
{

typedef struct 
{
    uint8_t mode;
    double pos;
    double posStiffness;
    double vel;
    double velStiffness;
    double torque;
} ServoCommand;

using CallbackReturn = rclcpp_lifecycle::node_interfaces::LifecycleNodeInterface::CallbackReturn;
using MotorState = robot_msgs::msg::MotorState;
using MotorCommand = robot_msgs::msg::MotorCommand;

class RobotJointController : public controller_interface::ControllerInterface
{
private:
    
    rclcpp::Subscription<MotorCommand>::SharedPtr joint_command_subscriber_;
    std::shared_ptr<realtime_tools::RealtimePublisher<MotorState>> joint_state_publisher_ ;

    void setCommandCB(const MotorCommand::SharedPtr msg);

public:
    ROBOT_JOINT_CONTROLLER_PUBLIC
    RobotJointController();

    ROBOT_JOINT_CONTROLLER_PUBLIC
    controller_interface::return_type init(const std::string & controller_name) override;

    ROBOT_JOINT_CONTROLLER_PUBLIC
    controller_interface::InterfaceConfiguration command_interface_configuration() const override;

    ROBOT_JOINT_CONTROLLER_PUBLIC
    controller_interface::InterfaceConfiguration state_interface_configuration() const override;

    ROBOT_JOINT_CONTROLLER_PUBLIC
    CallbackReturn on_configure(const rclcpp_lifecycle::State & previous_state) override;

    ROBOT_JOINT_CONTROLLER_PUBLIC
    CallbackReturn on_activate(const rclcpp_lifecycle::State & previous_state) override;

    ROBOT_JOINT_CONTROLLER_PUBLIC
    CallbackReturn on_deactivate(const rclcpp_lifecycle::State & previous_state) override;

    ROBOT_JOINT_CONTROLLER_PUBLIC
    controller_interface::return_type update() override;
    urdf::JointConstSharedPtr joint_urdf_;
    std::string joint_name_; 
    std::string robot_description_; 
    
    realtime_tools::RealtimeBuffer<robot_msgs::msg::MotorCommand> rt_cmd_buff;

    robot_msgs::msg::MotorCommand last_command_;
    robot_msgs::msg::MotorCommand last_servo_command_;
    robot_msgs::msg::MotorState last_state_;

    ServoCommand servo_command_;

    void positionLimits(double &position);
    void velocityLimits(double &velocity);
    void effortLimits(double &effort);
    double clamp(double &value, double min, double max);
};
}

#endif
