// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from robot_msgs:msg/RobotCommand.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "robot_msgs/msg/detail/robot_command__rosidl_typesupport_introspection_c.h"
#include "robot_msgs/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "robot_msgs/msg/detail/robot_command__functions.h"
#include "robot_msgs/msg/detail/robot_command__struct.h"


// Include directives for member types
// Member `motor_command`
#include "robot_msgs/msg/motor_command.h"
// Member `motor_command`
#include "robot_msgs/msg/detail/motor_command__rosidl_typesupport_introspection_c.h"

#ifdef __cplusplus
extern "C"
{
#endif

void RobotCommand__rosidl_typesupport_introspection_c__RobotCommand_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  robot_msgs__msg__RobotCommand__init(message_memory);
}

void RobotCommand__rosidl_typesupport_introspection_c__RobotCommand_fini_function(void * message_memory)
{
  robot_msgs__msg__RobotCommand__fini(message_memory);
}

size_t RobotCommand__rosidl_typesupport_introspection_c__size_function__MotorCommand__motor_command(
  const void * untyped_member)
{
  (void)untyped_member;
  return 32;
}

const void * RobotCommand__rosidl_typesupport_introspection_c__get_const_function__MotorCommand__motor_command(
  const void * untyped_member, size_t index)
{
  const robot_msgs__msg__MotorCommand ** member =
    (const robot_msgs__msg__MotorCommand **)(untyped_member);
  return &(*member)[index];
}

void * RobotCommand__rosidl_typesupport_introspection_c__get_function__MotorCommand__motor_command(
  void * untyped_member, size_t index)
{
  robot_msgs__msg__MotorCommand ** member =
    (robot_msgs__msg__MotorCommand **)(untyped_member);
  return &(*member)[index];
}

static rosidl_typesupport_introspection_c__MessageMember RobotCommand__rosidl_typesupport_introspection_c__RobotCommand_message_member_array[1] = {
  {
    "motor_command",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    true,  // is array
    32,  // array size
    false,  // is upper bound
    offsetof(robot_msgs__msg__RobotCommand, motor_command),  // bytes offset in struct
    NULL,  // default value
    RobotCommand__rosidl_typesupport_introspection_c__size_function__MotorCommand__motor_command,  // size() function pointer
    RobotCommand__rosidl_typesupport_introspection_c__get_const_function__MotorCommand__motor_command,  // get_const(index) function pointer
    RobotCommand__rosidl_typesupport_introspection_c__get_function__MotorCommand__motor_command,  // get(index) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers RobotCommand__rosidl_typesupport_introspection_c__RobotCommand_message_members = {
  "robot_msgs__msg",  // message namespace
  "RobotCommand",  // message name
  1,  // number of fields
  sizeof(robot_msgs__msg__RobotCommand),
  RobotCommand__rosidl_typesupport_introspection_c__RobotCommand_message_member_array,  // message members
  RobotCommand__rosidl_typesupport_introspection_c__RobotCommand_init_function,  // function to initialize message memory (memory has to be allocated)
  RobotCommand__rosidl_typesupport_introspection_c__RobotCommand_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t RobotCommand__rosidl_typesupport_introspection_c__RobotCommand_message_type_support_handle = {
  0,
  &RobotCommand__rosidl_typesupport_introspection_c__RobotCommand_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_robot_msgs
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, robot_msgs, msg, RobotCommand)() {
  RobotCommand__rosidl_typesupport_introspection_c__RobotCommand_message_member_array[0].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, robot_msgs, msg, MotorCommand)();
  if (!RobotCommand__rosidl_typesupport_introspection_c__RobotCommand_message_type_support_handle.typesupport_identifier) {
    RobotCommand__rosidl_typesupport_introspection_c__RobotCommand_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &RobotCommand__rosidl_typesupport_introspection_c__RobotCommand_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif
