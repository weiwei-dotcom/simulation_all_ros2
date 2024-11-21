// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from robot_msgs:msg/RobotState.idl
// generated code does not contain a copyright notice

#ifndef ROBOT_MSGS__MSG__DETAIL__ROBOT_STATE__TRAITS_HPP_
#define ROBOT_MSGS__MSG__DETAIL__ROBOT_STATE__TRAITS_HPP_

#include "robot_msgs/msg/detail/robot_state__struct.hpp"
#include <rosidl_runtime_cpp/traits.hpp>
#include <stdint.h>
#include <type_traits>

// Include directives for member types
// Member 'imu'
#include "robot_msgs/msg/detail/imu__traits.hpp"
// Member 'motor_state'
#include "robot_msgs/msg/detail/motor_state__traits.hpp"

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<robot_msgs::msg::RobotState>()
{
  return "robot_msgs::msg::RobotState";
}

template<>
inline const char * name<robot_msgs::msg::RobotState>()
{
  return "robot_msgs/msg/RobotState";
}

template<>
struct has_fixed_size<robot_msgs::msg::RobotState>
  : std::integral_constant<bool, has_fixed_size<robot_msgs::msg::IMU>::value && has_fixed_size<robot_msgs::msg::MotorState>::value> {};

template<>
struct has_bounded_size<robot_msgs::msg::RobotState>
  : std::integral_constant<bool, has_bounded_size<robot_msgs::msg::IMU>::value && has_bounded_size<robot_msgs::msg::MotorState>::value> {};

template<>
struct is_message<robot_msgs::msg::RobotState>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // ROBOT_MSGS__MSG__DETAIL__ROBOT_STATE__TRAITS_HPP_
