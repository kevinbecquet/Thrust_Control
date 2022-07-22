// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from thrust_msgs:msg/Thrust.idl
// generated code does not contain a copyright notice
#include "thrust_msgs/msg/detail/thrust__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>


// Include directives for member types
// Member `header`
#include "std_msgs/msg/detail/header__functions.h"

bool
thrust_msgs__msg__Thrust__init(thrust_msgs__msg__Thrust * msg)
{
  if (!msg) {
    return false;
  }
  // header
  if (!std_msgs__msg__Header__init(&msg->header)) {
    thrust_msgs__msg__Thrust__fini(msg);
    return false;
  }
  // thrust
  // alpha
  // kp
  // ki
  // kd
  // kff
  // mode
  return true;
}

void
thrust_msgs__msg__Thrust__fini(thrust_msgs__msg__Thrust * msg)
{
  if (!msg) {
    return;
  }
  // header
  std_msgs__msg__Header__fini(&msg->header);
  // thrust
  // alpha
  // kp
  // ki
  // kd
  // kff
  // mode
}

bool
thrust_msgs__msg__Thrust__are_equal(const thrust_msgs__msg__Thrust * lhs, const thrust_msgs__msg__Thrust * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // header
  if (!std_msgs__msg__Header__are_equal(
      &(lhs->header), &(rhs->header)))
  {
    return false;
  }
  // thrust
  if (lhs->thrust != rhs->thrust) {
    return false;
  }
  // alpha
  if (lhs->alpha != rhs->alpha) {
    return false;
  }
  // kp
  if (lhs->kp != rhs->kp) {
    return false;
  }
  // ki
  if (lhs->ki != rhs->ki) {
    return false;
  }
  // kd
  if (lhs->kd != rhs->kd) {
    return false;
  }
  // kff
  if (lhs->kff != rhs->kff) {
    return false;
  }
  // mode
  if (lhs->mode != rhs->mode) {
    return false;
  }
  return true;
}

bool
thrust_msgs__msg__Thrust__copy(
  const thrust_msgs__msg__Thrust * input,
  thrust_msgs__msg__Thrust * output)
{
  if (!input || !output) {
    return false;
  }
  // header
  if (!std_msgs__msg__Header__copy(
      &(input->header), &(output->header)))
  {
    return false;
  }
  // thrust
  output->thrust = input->thrust;
  // alpha
  output->alpha = input->alpha;
  // kp
  output->kp = input->kp;
  // ki
  output->ki = input->ki;
  // kd
  output->kd = input->kd;
  // kff
  output->kff = input->kff;
  // mode
  output->mode = input->mode;
  return true;
}

thrust_msgs__msg__Thrust *
thrust_msgs__msg__Thrust__create()
{
  thrust_msgs__msg__Thrust * msg = (thrust_msgs__msg__Thrust *)malloc(sizeof(thrust_msgs__msg__Thrust));
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(thrust_msgs__msg__Thrust));
  bool success = thrust_msgs__msg__Thrust__init(msg);
  if (!success) {
    free(msg);
    return NULL;
  }
  return msg;
}

void
thrust_msgs__msg__Thrust__destroy(thrust_msgs__msg__Thrust * msg)
{
  if (msg) {
    thrust_msgs__msg__Thrust__fini(msg);
  }
  free(msg);
}


bool
thrust_msgs__msg__Thrust__Sequence__init(thrust_msgs__msg__Thrust__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  thrust_msgs__msg__Thrust * data = NULL;
  if (size) {
    data = (thrust_msgs__msg__Thrust *)calloc(size, sizeof(thrust_msgs__msg__Thrust));
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = thrust_msgs__msg__Thrust__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        thrust_msgs__msg__Thrust__fini(&data[i - 1]);
      }
      free(data);
      return false;
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void
thrust_msgs__msg__Thrust__Sequence__fini(thrust_msgs__msg__Thrust__Sequence * array)
{
  if (!array) {
    return;
  }
  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      thrust_msgs__msg__Thrust__fini(&array->data[i]);
    }
    free(array->data);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  } else {
    // ensure that data, size, and capacity values are consistent
    assert(0 == array->size);
    assert(0 == array->capacity);
  }
}

thrust_msgs__msg__Thrust__Sequence *
thrust_msgs__msg__Thrust__Sequence__create(size_t size)
{
  thrust_msgs__msg__Thrust__Sequence * array = (thrust_msgs__msg__Thrust__Sequence *)malloc(sizeof(thrust_msgs__msg__Thrust__Sequence));
  if (!array) {
    return NULL;
  }
  bool success = thrust_msgs__msg__Thrust__Sequence__init(array, size);
  if (!success) {
    free(array);
    return NULL;
  }
  return array;
}

void
thrust_msgs__msg__Thrust__Sequence__destroy(thrust_msgs__msg__Thrust__Sequence * array)
{
  if (array) {
    thrust_msgs__msg__Thrust__Sequence__fini(array);
  }
  free(array);
}

bool
thrust_msgs__msg__Thrust__Sequence__are_equal(const thrust_msgs__msg__Thrust__Sequence * lhs, const thrust_msgs__msg__Thrust__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!thrust_msgs__msg__Thrust__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
thrust_msgs__msg__Thrust__Sequence__copy(
  const thrust_msgs__msg__Thrust__Sequence * input,
  thrust_msgs__msg__Thrust__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(thrust_msgs__msg__Thrust);
    thrust_msgs__msg__Thrust * data =
      (thrust_msgs__msg__Thrust *)realloc(output->data, allocation_size);
    if (!data) {
      return false;
    }
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!thrust_msgs__msg__Thrust__init(&data[i])) {
        /* free currently allocated and return false */
        for (; i-- > output->capacity; ) {
          thrust_msgs__msg__Thrust__fini(&data[i]);
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
    if (!thrust_msgs__msg__Thrust__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
