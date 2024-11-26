#include "robot_joint_controller_ros2.hpp"

#include <pluginlib/class_list_macros.h>

// #define rqtTune // use rqt or not

double clamp(double &value, double min, double max)
{
    if (value < min) {
        value = min;
    } else if (value > max) {
        value = max;
    }
    return value;
}

namespace robot_joint_controller
{

RobotJointController::RobotJointController()
{
    auto_declare("joint", 'joint_name');
    auto_declare("robot_description", 'robot_description');
    memset(&lastCommand_, 0, sizeof(robot_msgs::msg::MotorCommand));
    memset(&lastState_, 0, sizeof(robot_msgs::msg::MotorState));
    memset(&servoCommand_, 0, sizeof(ServoCommand));
}

RobotJointController::~RobotJointController()
{
    controller_state_publisher_.reset();
    sub_command_.reset();
}

// void RobotJointController::setCommandCB(const robot_msgs::msg::MotorCommandConstPtr &msg)
// {
//     lastCommand.q = msg->q;
//     lastCommand.kp = msg->kp;
//     lastCommand.dq = msg->dq;
//     lastCommand.kd = msg->kd;
//     lastCommand.tau = msg->tau;
//     // the writeFromNonRT can be used in RT, if you have the guarantee that
//     //  * no non-rt thread is calling the same function (we're not subscribing to ros callbacks)
//     //  * there is only one single rt thread
//     command.writeFromNonRT(lastCommand);
// }

void RobotJointController::setCommandCB(const MotorCommand::SharedPtr msg)
{
    lastCommand_.q = msg->q;
    lastCommand_.kp = msg->kp;
    lastCommand_.dq = msg->dq;
    lastCommand_.kd = msg->kd;
    lastCommand_.tau = msg->tau;
    // the writeFromNonRT can be used in RT, if you have the guarantee that
    //  * no non-rt thread is calling the same function (we're not subscribing to ros callbacks)
    //  * there is only one single rt thread
    command_.writeFromNonRT(lastCommand_);
}

controller_interface::return_type RobotJointController::init(const std::string & controller_name) {
    auto ret = ControllerInterface::init(controller_name);
    if (ret != controller_interface::return_type::OK) {
        RCLCPP_ERROR(ndoe_->get_logger(), "No joint given in namespace: '%s')", n.getNamespace().c_str());
    }

    auto_declare("joint", "joint_name");
    auto_declare("robot_description", "robot_description");

    std::string name_space = get_node()->get_namespace();
    sub_command_ = node_->create_subscription<MotorCommand>("command", 10,
        std::bind(&RobotJointController::setCommandCB,
            this,
            std::placeholders::_1));
    
    controller_state_publisher_ = std::make_shared<realtime_tools::RealtimePublisher<MotorState>>(
        node_->create_publisher<MotorState>(name_space + "/state", 1));

    return controller_interface::return_type::SUCCESS;
}

// // Controller initialization in non-realtime
// bool RobotJointController::init(hardware_interface::EffortJointInterface *robot, ros::NodeHandle &n)
// {
//     name_space = n.getNamespace();
//     if (!n.getParam("joint", joint_name)) {
//         ROS_ERROR("No joint given in namespace: '%s')", n.getNamespace().c_str());
//         return false;
//     }

//     // load pid param from ymal only if rqt need
// #ifdef rqtTune
//     // Load PID Controller using gains set on parameter server
//     if (!pid_controller_.init(ros::NodeHandle(n, "pid"))) return false;
// #endif

//     urdf::Model urdf;  // Get URDF info about joint
//     if (!urdf.initParamWithNodeHandle("robot_description", n)) {
//         ROS_ERROR("Failed to parse urdf file");
//         return false;
//     }
//     joint_urdf_ = urdf.getJoint(joint_name);
//     if (!joint_urdf_) {
//         ROS_ERROR("Could not find joint '%s' in urdf", joint_name.c_str());
//         return false;
//     }
//     joint = robot->getHandle(joint_name);

//     // Start command subscriber
//     sub_command_ = n.subscribe("command", 20, &RobotJointController::setCommandCB, this);

//     // Start realtime state publisher
//     controller_state_publisher_.reset(new realtime_tools::RealtimePublisher<robot_msgs::MotorState>(n, name_space + "/state", 1));

//     return true;
// }

RobotJointController::CallbackReturn RobotJointController::on_configure(const rclcpp_lifecycle::State &previous_state) {

    urdf::Model model;
    if (!model.initString(get_node()->get_parameter("robot_description").as_string())) {
        RCLCPP_ERROR(get_node()->get_logger(), "Failed to parse urdf file");
        return CallbackReturn::ERROR;
    }
    joint_name_ = get_node()->get_parameter("joint").as_string();
    joint_urdf_ = model.getJoint(joint_name_);
    if (!joint_urdf_) {
        RCLCPP_ERROR("Could not find joint '%s' in urdf", joint_name_.c_str());
        return CallbackReturn::ERROR;
    }

    return CallbackReturn::SUCCESS;
}

RobotJointController::CallbackReturn RobotJointController::on_activate(const rclcpp_lifecycle::State &previous_state) {
    auto command_interface_it = std::find_if(
        command_interfaces_.begin(), command_interfaces_.end(), 
        [](const hardware_interface::LoanedCommandInterface & command_interface) {
            return command_interface.get_interface_name() == hardware_interface::HW_IF_EFFORT;
        }
    );
    if (command_interface_it == command_interfaces_.end())
    {
        RCLCPP_ERROR(get_node()->get_logger(), "Expected 1 position command interface");
        return CallbackReturn::ERROR;
    }
    if (command_interface_it->get_name() != joint_name_)
    {
        RCLCPP_ERROR_STREAM(
        get_node()->get_logger(), "Position command interface is different than joint name `"
                                << command_interface_it->get_name() << "` != `" << joint_name_
                                << "`");
        return CallbackReturn::ERROR;
    }
    const auto pos_state_it = std::find_if(
        state_interfaces_.begin(), state_interfaces_.end(), 
        [](const hardware_interface::LoanedStateInterface & state_interface) {
            return state_interface.get_interface_name() == hardware_interface::HW_IF_POSITION;
        }
    );
    if (pos_state_it == state_interfaces_.end()) {
        RCLCPP_ERROR(get_node()->get_logger(), "Expected 1 position state interface");
        return CallbackReturn::ERROR;
    }
    if (pos_state_it->get_name() != joint_name_) {
        RCLCPP_ERROR_STREAM(
        get_node()->get_logger(), "Position state interface is different than joint name `"
                                << pos_state_it->get_name() << "` != `" << joint_name_
                                << "`");
        return CallbackReturn::ERROR;
    }
    const auto vel_state_it = std::find_if(
        state_interfaces_.begin(), state_interfaces_.end(),
        [] (const hardware_interface::LoanedStateInterface & state_interface) {
            return state_interface.get_interface_name() == hardware_interface::HW_IF_VELOCITY;
        }
    );
    if (vel_state_it == state_interfaces_.end()) {
        RCLCPP_ERROR(get_node()->get_logger(), "Expected 1 velocity state interface");
        return CallbackReturn::ERROR;
    }
    if (vel_state_it->get_name() != joint_name_) {
        RCLCPP_ERROR_STREAM(
            get_node()->get_logger(), "Velocity state interface is different than joint name `"
                                << vel_state_it->get_name() << "` != `" << joint_name_
                                << "`");
        return CallbackReturn::ERROR;
    }
    const auto eff_state_it = std::find_if(
        state_interfaces_.begin(), state_interfaces_.end(),
        [] (const hardware_interface::LoanedStateInterface & state_interface) {
            return state_interface.get_interface_name() == hardware_interface::HW_IF_EFFORT;
        }
    );
    if (eff_state_it == state_interfaces_.end()) {
        RCLCPP_ERROR(get_node()->get_logger(), "Expected 1 effort state interface");
        return CallbackReturn::ERROR;
    }
    if (eff_state_it->get_name() != joint_name_) {
        RCLCPP_ERROR_STREAM(
            get_node()->get_logger(), "Effort state interface is different than joint name `"
                                << eff_state_it->get_name() << "` != `" << joint_name_
                                << "`");
        return CallbackReturn::ERROR;
    }

    joint_command_interface_ = *command_interface_it;
    joint_state_.pos = *pos_state_it;
    joint_state_.vel = *vel_state_it;
    joint_state_.eff = *eff_state_it;

    double init_pos = joint.getPosition();
    lastCommand.q = init_pos;
    lastState.q = init_pos;
    lastCommand.dq = 0;
    lastState.dq = 0;
    lastCommand.tau = 0;
    lastState.tauEst = 0;
    command.initRT(lastCommand);

    pid_controller_.reset();

    return CallbackReturn::SUCCESS;
}

void RobotJointController::setGains(const double &p, const double &i, const double &d, const double &i_max, const double &i_min,
                                    const bool &antiwindup)
{
    pid_controller_.setGains(p, i, d, i_max, i_min, antiwindup);
}

void RobotJointController::getGains(double &p, double &i, double &d, double &i_max, double &i_min, bool &antiwindup)
{
    pid_controller_.getGains(p, i, d, i_max, i_min, antiwindup);
}

void RobotJointController::getGains(double &p, double &i, double &d, double &i_max, double &i_min)
{
    bool dummy;
    pid_controller_.getGains(p, i, d, i_max, i_min, dummy);
}

// Controller startup in realtime
void RobotJointController::starting(const ros::Time &time)
{
    double init_pos = joint.getPosition();
    lastCommand.q = init_pos;
    lastState.q = init_pos;
    lastCommand.dq = 0;
    lastState.dq = 0;
    lastCommand.tau = 0;
    lastState.tauEst = 0;
    command.initRT(lastCommand);

    pid_controller_.reset();
}

// Controller update loop in realtime
void RobotJointController::update(const ros::Time &time, const ros::Duration &period)
{
    double currentPos, currentVel, calcTorque;
    lastCommand = *(command.readFromRT());

    // set command data
    servoCommand.pos = lastCommand.q;
    positionLimits(servoCommand.pos);
    servoCommand.posStiffness = lastCommand.kp;
    if (fabs(lastCommand.q - PosStopF) < 0.00001) {
        servoCommand.posStiffness = 0;
    }
    servoCommand.vel = lastCommand.dq;
    velocityLimits(servoCommand.vel);
    servoCommand.velStiffness = lastCommand.kd;
    if (fabs(lastCommand.dq - VelStopF) < 0.00001) {
        servoCommand.velStiffness = 0;
    }
    servoCommand.torque = lastCommand.tau;
    effortLimits(servoCommand.torque);

    // rqt set P D gains
#ifdef rqtTune
    double i, i_max, i_min;
    getGains(servoCommand.posStiffness, i, servoCommand.velStiffness, i_max, i_min);
#endif

    currentPos = joint_command_interface_.get_value();
    // currentVel = computeVel(currentPos, (double)lastState.q, (double)lastState.dq, period.toSec());
    // calcTorque = computeTorque(currentPos, currentVel, servoCommand);
    currentVel = (currentPos - (double)lastState.q) / period.toSec();
    calcTorque = servoCommand.posStiffness * (servoCommand.pos - currentPos) + servoCommand.velStiffness * (servoCommand.vel - currentVel) +
                 servoCommand.torque;
    effortLimits(calcTorque);

    //
    joint_command_interface_.set_value(calcTorque);

    // joint_command_interface_.setCommand(servoCommand.pos);

    lastState.q = currentPos;
    lastState.dq = currentVel;
    // lastState.tauEst = calcTorque;
    lastState.tauEst = joint_command_interface_.getEffort();

    // publish state
    if (controller_state_publisher_ && controller_state_publisher_->trylock()) {
        controller_state_publisher_->msg_.q = lastState.q;
        controller_state_publisher_->msg_.dq = lastState.dq;
        controller_state_publisher_->msg_.tauEst = lastState.tauEst;
        controller_state_publisher_->unlockAndPublish();
    }
}

// Controller stopping in realtime
void RobotJointController::stopping() {}

void RobotJointController::positionLimits(double &position)
{
    if (joint_urdf_->type == urdf::Joint::REVOLUTE || joint_urdf_->type == urdf::Joint::PRISMATIC)
        clamp(position, joint_urdf_->limits->lower, joint_urdf_->limits->upper);
}

void RobotJointController::velocityLimits(double &velocity)
{
    if (joint_urdf_->type == urdf::Joint::REVOLUTE || joint_urdf_->type == urdf::Joint::PRISMATIC)
        clamp(velocity, -joint_urdf_->limits->velocity, joint_urdf_->limits->velocity);
}

void RobotJointController::effortLimits(double &effort)
{
    if (joint_urdf_->type == urdf::Joint::REVOLUTE || joint_urdf_->type == urdf::Joint::PRISMATIC)
        clamp(effort, -joint_urdf_->limits->effort, joint_urdf_->limits->effort);
}

}  // namespace robot_joint_controller

// Register controller to pluginlib
PLUGINLIB_EXPORT_CLASS(robot_joint_controller::RobotJointController, controller_interface::ControllerBase);
