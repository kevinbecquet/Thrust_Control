// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from thrust_msgs:msg/Thrust.idl
// generated code does not contain a copyright notice

#ifndef THRUST_MSGS__MSG__DETAIL__THRUST__STRUCT_H_
#define THRUST_MSGS__MSG__DETAIL__THRUST__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__struct.h"

// Struct defined in msg/Thrust in the package thrust_msgs.
typedef struct thrust_msgs__msg__Thrust
{
  std_msgs__msg__Header header;
  double thrust_meas;
  double thrust_comm;
  double thrust_comp;
  double alpha;
  double kp;
  double ki;
  double kd;
  double kff;
  uint16_t pulse;
  uint16_t mode;
} thrust_msgs__msg__Thrust;

// Struct for a sequence of thrust_msgs__msg__Thrust.
typedef struct thrust_msgs__msg__Thrust__Sequence
{
  thrust_msgs__msg__Thrust * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} thrust_msgs__msg__Thrust__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // THRUST_MSGS__MSG__DETAIL__THRUST__STRUCT_H_
