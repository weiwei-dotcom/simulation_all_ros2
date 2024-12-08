#include "robot_joint_controller.hpp"
#include <pluginlib/class_list_macros.h>

// #define rqtTune // use rqt or not

namespace robot_joint_controller
{

RobotJointController::RobotJointController()
: controller_interface::ControllerInterface(),
    joint_urdf_(nullptr)
{
}

double RobotJointController::clamp(double &value, double min, double max)
{
    if (value < min) {
        value = min;
    } else if (value > max) {
        value = max;
    }
    return value;
}

void RobotJointController::setCommandCB(const MotorCommand::SharedPtr msg)
{
    MotorCommand recieve_cmd;
    recieve_cmd.q = msg->q;
    recieve_cmd.kp = msg->kp;
    recieve_cmd.dq = msg->dq;
    recieve_cmd.kd = msg->kd;
    recieve_cmd.tau = msg->tau;

    // the writeFromNonRT can be used in RT, if you have the guarantee that
    //  * no non-rt thread is calling the same function (we're not subscribing to ros callbacks)
    //  * there is only one single rt thread
    rt_cmd_buff.writeFromNonRT(recieve_cmd);
}

controller_interface::return_type RobotJointController::init(const std::string & controller_name) {
    auto ret = ControllerInterface::init(controller_name);
    if (ret != controller_interface::return_type::OK)
    {
        return ret;
    }
    try 
    {
        joint_name_ = auto_declare<std::string>("joint", joint_name_);
        robot_description_ = auto_declare<std::string>("robot_description", robot_description_); //之后launch文件中要先将param参数使用controller_manager robot_state_publisher发布
    }
    catch (const std::exception & e)
    {
        fprintf(stderr, "Exception thrown during init stage with message: %s \n", e.what());
        return controller_interface::return_type::ERROR;
    }
    return controller_interface::return_type::SUCCESS;
}

CallbackReturn RobotJointController::on_configure(const rclcpp_lifecycle::State & previous_state) 
{
    robot_description_ = get_node()->get_parameter("robot_description").as_string();
    // 临时 URDF 文件路径
    std::string tempUrdfFile = "/tmp/temp_urdf.urdf";
    // 构造 xacro 命令
    std::string command = "xacro " + robot_description_ + " > " + tempUrdfFile;
    // 执行命令
    int ret = system(command.c_str());
    if (ret != 0) {
        throw std::runtime_error("Failed to execute xacro command.");
    }
    // 读取生成的 URDF 文件内容
    std::ifstream urdfFile(tempUrdfFile);
    if (!urdfFile.is_open()) {
        throw std::runtime_error("Failed to open temporary URDF file.");
    }
    std::stringstream urdfContent;
    urdfContent << urdfFile.rdbuf(); // 读取文件内容到字符串流
    urdfFile.close();
    // 删除临时文件（可选）
    std::remove(tempUrdfFile.c_str());

    urdf::Model model;
    if (!model.initString(urdfContent.str().c_str())) {
        RCLCPP_ERROR(get_node()->get_logger(), "Failed to parse urdf file");
        return CallbackReturn::ERROR;
    }

    RCLCPP_INFO(get_node()->get_logger(), "read urdf success !  ! !");

    joint_name_ = get_node()->get_parameter("joint").as_string();
    RCLCPP_WARN(get_node()->get_logger(), "joint name is :  %s", joint_name_.c_str());


    if (joint_name_.empty())
    {
        RCLCPP_ERROR(get_node()->get_logger(), "'joint' parameter was empty");
        return CallbackReturn::ERROR;
    }
    joint_urdf_ = model.getJoint(joint_name_);
    if (!joint_urdf_) {
        RCLCPP_ERROR(get_node()->get_logger(), "Could not find joint '%s' in urdf", joint_name_.c_str());
        return CallbackReturn::ERROR;
    }
    return CallbackReturn::SUCCESS;
}

controller_interface::InterfaceConfiguration
RobotJointController::command_interface_configuration() const
{
    controller_interface::InterfaceConfiguration command_interfaces_config;
    command_interfaces_config.type = controller_interface::interface_configuration_type::INDIVIDUAL;
    command_interfaces_config.names.push_back(this->joint_name_ + "/effort");
    return command_interfaces_config;
}

controller_interface::InterfaceConfiguration
RobotJointController::state_interface_configuration() const
{
    controller_interface::InterfaceConfiguration state_interfaces_config;
    state_interfaces_config.type = controller_interface::interface_configuration_type::INDIVIDUAL;
    state_interfaces_config.names.push_back(this->joint_name_ + "/position");
    state_interfaces_config.names.push_back(this->joint_name_ + "/velocity");
    state_interfaces_config.names.push_back(this->joint_name_ + "/effort");
    return state_interfaces_config;
}

RobotJointController::CallbackReturn RobotJointController::on_activate(const rclcpp_lifecycle::State &previous_state) 
{
    std::string name_space = get_node()->get_namespace();

    joint_command_subscriber_ = get_node()->create_subscription<MotorCommand>("~/command", rclcpp::SystemDefaultsQoS(),
        std::bind(&RobotJointController::setCommandCB,
            this,
            std::placeholders::_1));
    joint_state_publisher_ = std::make_shared<realtime_tools::RealtimePublisher<MotorState>>(
        get_node()->create_publisher<MotorState>("~/state", rclcpp::SystemDefaultsQoS()));

    double init_pos = state_interfaces_[0].get_value();
    last_command_.q = init_pos;
    last_state_.q = init_pos;
    last_command_.dq = 0;
    last_state_.dq = 0;
    last_command_.tau = 0;
    last_state_.tau_est = 0;
    rt_cmd_buff.initRT(last_command_);

    return CallbackReturn::SUCCESS;
}

controller_interface::return_type RobotJointController::update() {
    double currentPos, currentVel, currentTau, calcTorque;
    robot_msgs::msg::MotorCommand current_command = *(rt_cmd_buff.readFromRT());

    // set command data
    robot_msgs::msg::MotorCommand current_servo_command = current_command;
    positionLimits(current_servo_command.q);
    if (fabs(current_command.q - PosStopF) < 0.00001) {
        current_servo_command.kp = 0;
    }
    velocityLimits(current_servo_command.dq);
    if (fabs(current_command.dq - VelStopF) < 0.00001) {
        current_servo_command.kd = 0;
    }
    effortLimits(current_servo_command.tau);

    currentPos = state_interfaces_[0].get_value();
    currentVel = state_interfaces_[1].get_value();
    // // 也可以使用位置差分的方式计算速度
    // currentVel = currentPos - last_state_.q;
    calcTorque = current_servo_command.kp * (current_servo_command.q - currentPos) + current_servo_command.kd * (current_servo_command.dq - currentVel) +
                 current_servo_command.tau;
    effortLimits(calcTorque);
    //
    command_interfaces_[0].set_value(calcTorque);

    last_servo_command_ = current_servo_command;
    last_command_ = current_command;

    currentTau = state_interfaces_[2].get_value();
    // publish state
    if (joint_state_publisher_ && joint_state_publisher_->trylock()) {
        joint_state_publisher_->msg_.q = currentPos;
        joint_state_publisher_->msg_.dq = currentVel;
        joint_state_publisher_->msg_.tau_est = currentTau;
        joint_state_publisher_->unlockAndPublish();
    }
    last_state_.q = currentPos;
    last_state_.dq = currentVel;
    last_state_.tau_est = currentTau;
    return controller_interface::return_type::SUCCESS;
}

RobotJointController::CallbackReturn RobotJointController::on_deactivate(const rclcpp_lifecycle::State &previous_state) {
    joint_state_publisher_.reset();
    joint_command_subscriber_.reset();
    release_interfaces();
    return RobotJointController::CallbackReturn::SUCCESS;
}

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

PLUGINLIB_EXPORT_CLASS(robot_joint_controller::RobotJointController, controller_interface::ControllerInterface);
