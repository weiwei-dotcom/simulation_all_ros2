// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from robot_msgs:msg/MotorState.idl
// generated code does not contain a copyright notice

#ifndef ROBOT_MSGS__MSG__DETAIL__MOTOR_STATE__BUILDER_HPP_
#define ROBOT_MSGS__MSG__DETAIL__MOTOR_STATE__BUILDER_HPP_

#include "robot_msgs/msg/detail/motor_state__struct.hpp"
#include <rosidl_runtime_cpp/message_initialization.hpp>
#include <algorithm>
#include <utility>


namespace robot_msgs
{

namespace msg
{

namespace builder
{

class Init_MotorState_cur
{
public:
  explicit Init_MotorState_cur(::robot_msgs::msg::MotorState & msg)
  : msg_(msg)
  {}
  ::robot_msgs::msg::MotorState cur(::robot_msgs::msg::MotorState::_cur_type arg)
  {
    msg_.cur = std::move(arg);
    return std::move(msg_);
  }

private:
  ::robot_msgs::msg::MotorState msg_;
};

class Init_MotorState_tau_est
{
public:
  explicit Init_MotorState_tau_est(::robot_msgs::msg::MotorState & msg)
  : msg_(msg)
  {}
  Init_MotorState_cur tau_est(::robot_msgs::msg::MotorState::_tau_est_type arg)
  {
    msg_.tau_est = std::move(arg);
    return Init_MotorState_cur(msg_);
  }

private:
  ::robot_msgs::msg::MotorState msg_;
};

class Init_MotorState_ddq
{
public:
  explicit Init_MotorState_ddq(::robot_msgs::msg::MotorState & msg)
  : msg_(msg)
  {}
  Init_MotorState_tau_est ddq(::robot_msgs::msg::MotorState::_ddq_type arg)
  {
    msg_.ddq = std::move(arg);
    return Init_MotorState_tau_est(msg_);
  }

private:
  ::robot_msgs::msg::MotorState msg_;
};

class Init_MotorState_dq
{
public:
  explicit Init_MotorState_dq(::robot_msgs::msg::MotorState & msg)
  : msg_(msg)
  {}
  Init_MotorState_ddq dq(::robot_msgs::msg::MotorState::_dq_type arg)
  {
    msg_.dq = std::move(arg);
    return Init_MotorState_ddq(msg_);
  }

private:
  ::robot_msgs::msg::MotorState msg_;
};

class Init_MotorState_q
{
public:
  Init_MotorState_q()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_MotorState_dq q(::robot_msgs::msg::MotorState::_q_type arg)
  {
    msg_.q = std::move(arg);
    return Init_MotorState_dq(msg_);
  }

private:
  ::robot_msgs::msg::MotorState msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::robot_msgs::msg::MotorState>()
{
  return robot_msgs::msg::builder::Init_MotorState_q();
}

}  // namespace robot_msgs

#endif  // ROBOT_MSGS__MSG__DETAIL__MOTOR_STATE__BUILDER_HPP_
