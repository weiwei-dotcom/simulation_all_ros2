#ifndef ROBOT_JOINT_CONTROLLER_HPP
#define ROBOT_JOINT_CONTROLLER_HPP

#include <rclcpp/rclcpp.hpp>
#include <urdf/model.h>
#include <control_toolbox/pid.hpp> // 这个是由于可能rqt调试需要用到， 可以删掉
#include <realtime_tools/realtime_publisher.h>
#include <hardware_interface/loaned_command_interface.hpp>
#include <controller_interface/controller_interface.hpp>
#include <hardware_interface/types/hardware_interface_type_values.hpp>
#include <std_msgs/msg/float64.h>
#include <realtime_tools/realtime_buffer.h>
#include "robot_msgs/msg/motor_command.hpp"
#include "robot_msgs/msg/motor_state.hpp"
#include <geometry_msgs/msg/wrench_stamped.hpp>

#include <stdio.h>
#include <stdint.h>
#include <algorithm>
#include <math.h>
#include <cstring>
#include <string.h>

#define PosStopF  (2.146E+9f)
#define VelStopF  (16000.0f)

typedef struct 
{
    uint8_t mode;
    double pos;
    double posStiffness;
    double vel;
    double velStiffness;
    double torque;
} ServoCommand;

typedef struct 
{
    std::reference_wrapper<hardware_interface::LoanedStateInterface> pos; //todo:
    std::reference_wrapper<hardware_interface::LoanedStateInterface> vel; //todo:
    std::reference_wrapper<hardware_interface::LoanedStateInterface> eff; //todo:
} JointState;

namespace robot_joint_controller
{
class RobotJointController: public controller_interface::ControllerInterface
{
private:
    using CallbackReturn = rclcpp_lifecycle::node_interfaces::LifecycleNodeInterface::CallbackReturn;
    using MotorState = robot_msgs::msg::MotorState;
    using MotorCommand = robot_msgs::msg::MotorCommand;
    
    std::reference_wrapper<hardware_interface::LoanedCommandInterface> joint_command_interface_; //todo:
    JointState joint_state_;
    rclcpp::Subscription<robot_msgs::msg::MotorCommand>::SharedPtr joint_command_subscriber_;
    std::shared_ptr<realtime_tools::RealtimePublisher<robot_msgs::msg::MotorState>> joint_state_publisher_ ;

public:
    urdf::JointConstSharedPtr joint_urdf_;
    std::string joint_name_; 
    realtime_tools::RealtimeBuffer<robot_msgs::msg::MotorCommand> realtime_cmd_buffer_;

    robot_msgs::msg::MotorCommand last_command_;
    robot_msgs::msg::MotorCommand last_servo_command_;
    robot_msgs::msg::MotorState last_state_;

    ServoCommand servo_command_;

    RobotJointController();
    ~RobotJointController();
    controller_interface::return_type init(const std::string & controller_name) override;
    controller_interface::return_type update() override;
    CallbackReturn on_configure(const rclcpp_lifecycle::State &previous_state) override;
    CallbackReturn on_activate(const rclcpp_lifecycle::State &previous_state) override;
    CallbackReturn on_deactivate(const rclcpp_lifecycle::State &previous_state) override;

    void setCommandCB(const robot_msgs::msg::MotorCommand::SharedPtr msg);
    void positionLimits(double &position);
    void velocityLimits(double &velocity);
    void effortLimits(double &effort);
};
}

#endif
