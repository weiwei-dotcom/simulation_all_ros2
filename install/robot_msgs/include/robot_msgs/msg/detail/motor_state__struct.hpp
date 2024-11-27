// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from robot_msgs:msg/MotorState.idl
// generated code does not contain a copyright notice

#ifndef ROBOT_MSGS__MSG__DETAIL__MOTOR_STATE__STRUCT_HPP_
#define ROBOT_MSGS__MSG__DETAIL__MOTOR_STATE__STRUCT_HPP_

#include <rosidl_runtime_cpp/bounded_vector.hpp>
#include <rosidl_runtime_cpp/message_initialization.hpp>
#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>


#ifndef _WIN32
# define DEPRECATED__robot_msgs__msg__MotorState __attribute__((deprecated))
#else
# define DEPRECATED__robot_msgs__msg__MotorState __declspec(deprecated)
#endif

namespace robot_msgs
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct MotorState_
{
  using Type = MotorState_<ContainerAllocator>;

  explicit MotorState_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->q = 0.0;
      this->dq = 0.0;
      this->ddq = 0.0;
      this->tau_est = 0.0;
      this->cur = 0.0;
    }
  }

  explicit MotorState_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->q = 0.0;
      this->dq = 0.0;
      this->ddq = 0.0;
      this->tau_est = 0.0;
      this->cur = 0.0;
    }
  }

  // field types and members
  using _q_type =
    double;
  _q_type q;
  using _dq_type =
    double;
  _dq_type dq;
  using _ddq_type =
    double;
  _ddq_type ddq;
  using _tau_est_type =
    double;
  _tau_est_type tau_est;
  using _cur_type =
    double;
  _cur_type cur;

  // setters for named parameter idiom
  Type & set__q(
    const double & _arg)
  {
    this->q = _arg;
    return *this;
  }
  Type & set__dq(
    const double & _arg)
  {
    this->dq = _arg;
    return *this;
  }
  Type & set__ddq(
    const double & _arg)
  {
    this->ddq = _arg;
    return *this;
  }
  Type & set__tau_est(
    const double & _arg)
  {
    this->tau_est = _arg;
    return *this;
  }
  Type & set__cur(
    const double & _arg)
  {
    this->cur = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    robot_msgs::msg::MotorState_<ContainerAllocator> *;
  using ConstRawPtr =
    const robot_msgs::msg::MotorState_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<robot_msgs::msg::MotorState_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<robot_msgs::msg::MotorState_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      robot_msgs::msg::MotorState_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<robot_msgs::msg::MotorState_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      robot_msgs::msg::MotorState_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<robot_msgs::msg::MotorState_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<robot_msgs::msg::MotorState_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<robot_msgs::msg::MotorState_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__robot_msgs__msg__MotorState
    std::shared_ptr<robot_msgs::msg::MotorState_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__robot_msgs__msg__MotorState
    std::shared_ptr<robot_msgs::msg::MotorState_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const MotorState_ & other) const
  {
    if (this->q != other.q) {
      return false;
    }
    if (this->dq != other.dq) {
      return false;
    }
    if (this->ddq != other.ddq) {
      return false;
    }
    if (this->tau_est != other.tau_est) {
      return false;
    }
    if (this->cur != other.cur) {
      return false;
    }
    return true;
  }
  bool operator!=(const MotorState_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct MotorState_

// alias to use template instance with default allocator
using MotorState =
  robot_msgs::msg::MotorState_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace robot_msgs

#endif  // ROBOT_MSGS__MSG__DETAIL__MOTOR_STATE__STRUCT_HPP_
