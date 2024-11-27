// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from robot_msgs:msg/RobotState.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "robot_msgs/msg/detail/robot_state__rosidl_typesupport_introspection_c.h"
#include "robot_msgs/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "robot_msgs/msg/detail/robot_state__functions.h"
#include "robot_msgs/msg/detail/robot_state__struct.h"


// Include directives for member types
// Member `imu`
#include "robot_msgs/msg/imu.h"
// Member `imu`
#include "robot_msgs/msg/detail/imu__rosidl_typesupport_introspection_c.h"
// Member `motor_state`
#include "robot_msgs/msg/motor_state.h"
// Member `motor_state`
#include "robot_msgs/msg/detail/motor_state__rosidl_typesupport_introspection_c.h"

#ifdef __cplusplus
extern "C"
{
#endif

void RobotState__rosidl_typesupport_introspection_c__RobotState_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  robot_msgs__msg__RobotState__init(message_memory);
}

void RobotState__rosidl_typesupport_introspection_c__RobotState_fini_function(void * message_memory)
{
  robot_msgs__msg__RobotState__fini(message_memory);
}

size_t RobotState__rosidl_typesupport_introspection_c__size_function__MotorState__motor_state(
  const void * untyped_member)
{
  (void)untyped_member;
  return 32;
}

const void * RobotState__rosidl_typesupport_introspection_c__get_const_function__MotorState__motor_state(
  const void * untyped_member, size_t index)
{
  const robot_msgs__msg__MotorState ** member =
    (const robot_msgs__msg__MotorState **)(untyped_member);
  return &(*member)[index];
}

void * RobotState__rosidl_typesupport_introspection_c__get_function__MotorState__motor_state(
  void * untyped_member, size_t index)
{
  robot_msgs__msg__MotorState ** member =
    (robot_msgs__msg__MotorState **)(untyped_member);
  return &(*member)[index];
}

static rosidl_typesupport_introspection_c__MessageMember RobotState__rosidl_typesupport_introspection_c__RobotState_message_member_array[2] = {
  {
    "imu",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(robot_msgs__msg__RobotState, imu),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "motor_state",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    true,  // is array
    32,  // array size
    false,  // is upper bound
    offsetof(robot_msgs__msg__RobotState, motor_state),  // bytes offset in struct
    NULL,  // default value
    RobotState__rosidl_typesupport_introspection_c__size_function__MotorState__motor_state,  // size() function pointer
    RobotState__rosidl_typesupport_introspection_c__get_const_function__MotorState__motor_state,  // get_const(index) function pointer
    RobotState__rosidl_typesupport_introspection_c__get_function__MotorState__motor_state,  // get(index) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers RobotState__rosidl_typesupport_introspection_c__RobotState_message_members = {
  "robot_msgs__msg",  // message namespace
  "RobotState",  // message name
  2,  // number of fields
  sizeof(robot_msgs__msg__RobotState),
  RobotState__rosidl_typesupport_introspection_c__RobotState_message_member_array,  // message members
  RobotState__rosidl_typesupport_introspection_c__RobotState_init_function,  // function to initialize message memory (memory has to be allocated)
  RobotState__rosidl_typesupport_introspection_c__RobotState_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t RobotState__rosidl_typesupport_introspection_c__RobotState_message_type_support_handle = {
  0,
  &RobotState__rosidl_typesupport_introspection_c__RobotState_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_robot_msgs
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, robot_msgs, msg, RobotState)() {
  RobotState__rosidl_typesupport_introspection_c__RobotState_message_member_array[0].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, robot_msgs, msg, IMU)();
  RobotState__rosidl_typesupport_introspection_c__RobotState_message_member_array[1].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, robot_msgs, msg, MotorState)();
  if (!RobotState__rosidl_typesupport_introspection_c__RobotState_message_type_support_handle.typesupport_identifier) {
    RobotState__rosidl_typesupport_introspection_c__RobotState_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &RobotState__rosidl_typesupport_introspection_c__RobotState_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif
