// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from robot_msgs:msg/MotorCommand.idl
// generated code does not contain a copyright notice
#include "robot_msgs/msg/detail/motor_command__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


bool
robot_msgs__msg__MotorCommand__init(robot_msgs__msg__MotorCommand * msg)
{
  if (!msg) {
    return false;
  }
  // q
  // dq
  // tau
  // kp
  // kd
  return true;
}

void
robot_msgs__msg__MotorCommand__fini(robot_msgs__msg__MotorCommand * msg)
{
  if (!msg) {
    return;
  }
  // q
  // dq
  // tau
  // kp
  // kd
}

bool
robot_msgs__msg__MotorCommand__are_equal(const robot_msgs__msg__MotorCommand * lhs, const robot_msgs__msg__MotorCommand * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // q
  if (lhs->q != rhs->q) {
    return false;
  }
  // dq
  if (lhs->dq != rhs->dq) {
    return false;
  }
  // tau
  if (lhs->tau != rhs->tau) {
    return false;
  }
  // kp
  if (lhs->kp != rhs->kp) {
    return false;
  }
  // kd
  if (lhs->kd != rhs->kd) {
    return false;
  }
  return true;
}

bool
robot_msgs__msg__MotorCommand__copy(
  const robot_msgs__msg__MotorCommand * input,
  robot_msgs__msg__MotorCommand * output)
{
  if (!input || !output) {
    return false;
  }
  // q
  output->q = input->q;
  // dq
  output->dq = input->dq;
  // tau
  output->tau = input->tau;
  // kp
  output->kp = input->kp;
  // kd
  output->kd = input->kd;
  return true;
}

robot_msgs__msg__MotorCommand *
robot_msgs__msg__MotorCommand__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  robot_msgs__msg__MotorCommand * msg = (robot_msgs__msg__MotorCommand *)allocator.allocate(sizeof(robot_msgs__msg__MotorCommand), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(robot_msgs__msg__MotorCommand));
  bool success = robot_msgs__msg__MotorCommand__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
robot_msgs__msg__MotorCommand__destroy(robot_msgs__msg__MotorCommand * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    robot_msgs__msg__MotorCommand__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
robot_msgs__msg__MotorCommand__Sequence__init(robot_msgs__msg__MotorCommand__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  robot_msgs__msg__MotorCommand * data = NULL;

  if (size) {
    data = (robot_msgs__msg__MotorCommand *)allocator.zero_allocate(size, sizeof(robot_msgs__msg__MotorCommand), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = robot_msgs__msg__MotorCommand__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        robot_msgs__msg__MotorCommand__fini(&data[i - 1]);
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
robot_msgs__msg__MotorCommand__Sequence__fini(robot_msgs__msg__MotorCommand__Sequence * array)
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
      robot_msgs__msg__MotorCommand__fini(&array->data[i]);
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

robot_msgs__msg__MotorCommand__Sequence *
robot_msgs__msg__MotorCommand__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  robot_msgs__msg__MotorCommand__Sequence * array = (robot_msgs__msg__MotorCommand__Sequence *)allocator.allocate(sizeof(robot_msgs__msg__MotorCommand__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = robot_msgs__msg__MotorCommand__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
robot_msgs__msg__MotorCommand__Sequence__destroy(robot_msgs__msg__MotorCommand__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    robot_msgs__msg__MotorCommand__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
robot_msgs__msg__MotorCommand__Sequence__are_equal(const robot_msgs__msg__MotorCommand__Sequence * lhs, const robot_msgs__msg__MotorCommand__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!robot_msgs__msg__MotorCommand__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
robot_msgs__msg__MotorCommand__Sequence__copy(
  const robot_msgs__msg__MotorCommand__Sequence * input,
  robot_msgs__msg__MotorCommand__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(robot_msgs__msg__MotorCommand);
    robot_msgs__msg__MotorCommand * data =
      (robot_msgs__msg__MotorCommand *)realloc(output->data, allocation_size);
    if (!data) {
      return false;
    }
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!robot_msgs__msg__MotorCommand__init(&data[i])) {
        /* free currently allocated and return false */
        for (; i-- > output->capacity; ) {
          robot_msgs__msg__MotorCommand__fini(&data[i]);
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
    if (!robot_msgs__msg__MotorCommand__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
