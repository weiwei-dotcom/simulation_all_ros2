// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from robot_msgs:msg/RobotCommand.idl
// generated code does not contain a copyright notice
#include "robot_msgs/msg/detail/robot_command__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `motor_command`
#include "robot_msgs/msg/detail/motor_command__functions.h"

bool
robot_msgs__msg__RobotCommand__init(robot_msgs__msg__RobotCommand * msg)
{
  if (!msg) {
    return false;
  }
  // motor_command
  for (size_t i = 0; i < 32; ++i) {
    if (!robot_msgs__msg__MotorCommand__init(&msg->motor_command[i])) {
      robot_msgs__msg__RobotCommand__fini(msg);
      return false;
    }
  }
  return true;
}

void
robot_msgs__msg__RobotCommand__fini(robot_msgs__msg__RobotCommand * msg)
{
  if (!msg) {
    return;
  }
  // motor_command
  for (size_t i = 0; i < 32; ++i) {
    robot_msgs__msg__MotorCommand__fini(&msg->motor_command[i]);
  }
}

bool
robot_msgs__msg__RobotCommand__are_equal(const robot_msgs__msg__RobotCommand * lhs, const robot_msgs__msg__RobotCommand * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // motor_command
  for (size_t i = 0; i < 32; ++i) {
    if (!robot_msgs__msg__MotorCommand__are_equal(
        &(lhs->motor_command[i]), &(rhs->motor_command[i])))
    {
      return false;
    }
  }
  return true;
}

bool
robot_msgs__msg__RobotCommand__copy(
  const robot_msgs__msg__RobotCommand * input,
  robot_msgs__msg__RobotCommand * output)
{
  if (!input || !output) {
    return false;
  }
  // motor_command
  for (size_t i = 0; i < 32; ++i) {
    if (!robot_msgs__msg__MotorCommand__copy(
        &(input->motor_command[i]), &(output->motor_command[i])))
    {
      return false;
    }
  }
  return true;
}

robot_msgs__msg__RobotCommand *
robot_msgs__msg__RobotCommand__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  robot_msgs__msg__RobotCommand * msg = (robot_msgs__msg__RobotCommand *)allocator.allocate(sizeof(robot_msgs__msg__RobotCommand), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(robot_msgs__msg__RobotCommand));
  bool success = robot_msgs__msg__RobotCommand__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
robot_msgs__msg__RobotCommand__destroy(robot_msgs__msg__RobotCommand * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    robot_msgs__msg__RobotCommand__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
robot_msgs__msg__RobotCommand__Sequence__init(robot_msgs__msg__RobotCommand__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  robot_msgs__msg__RobotCommand * data = NULL;

  if (size) {
    data = (robot_msgs__msg__RobotCommand *)allocator.zero_allocate(size, sizeof(robot_msgs__msg__RobotCommand), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = robot_msgs__msg__RobotCommand__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        robot_msgs__msg__RobotCommand__fini(&data[i - 1]);
      }
      allocator.deallocate(data, allocator.state);
      return false;
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void
robot_msgs__msg__RobotCommand__Sequence__fini(robot_msgs__msg__RobotCommand__Sequence * array)
{
  if (!array) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();

  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      robot_msgs__msg__RobotCommand__fini(&array->data[i]);
    }
    allocator.deallocate(array->data, allocator.state);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  } else {
    // ensure that data, size, and capacity values are consistent
    assert(0 == array->size);
    assert(0 == array->capacity);
  }
}

robot_msgs__msg__RobotCommand__Sequence *
robot_msgs__msg__RobotCommand__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  robot_msgs__msg__RobotCommand__Sequence * array = (robot_msgs__msg__RobotCommand__Sequence *)allocator.allocate(sizeof(robot_msgs__msg__RobotCommand__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = robot_msgs__msg__RobotCommand__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
robot_msgs__msg__RobotCommand__Sequence__destroy(robot_msgs__msg__RobotCommand__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    robot_msgs__msg__RobotCommand__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
robot_msgs__msg__RobotCommand__Sequence__are_equal(const robot_msgs__msg__RobotCommand__Sequence * lhs, const robot_msgs__msg__RobotCommand__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!robot_msgs__msg__RobotCommand__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
robot_msgs__msg__RobotCommand__Sequence__copy(
  const robot_msgs__msg__RobotCommand__Sequence * input,
  robot_msgs__msg__RobotCommand__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(robot_msgs__msg__RobotCommand);
    robot_msgs__msg__RobotCommand * data =
      (robot_msgs__msg__RobotCommand *)realloc(output->data, allocation_size);
    if (!data) {
      return false;
    }
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!robot_msgs__msg__RobotCommand__init(&data[i])) {
        /* free currently allocated and return false */
        for (; i-- > output->capacity; ) {
          robot_msgs__msg__RobotCommand__fini(&data[i]);
        }
        free(data);
        return false;
      }
    }
    output->data = data;
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!robot_msgs__msg__RobotCommand__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
