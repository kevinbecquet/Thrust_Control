// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from thrust_msgs:msg/Thrust.idl
// generated code does not contain a copyright notice

#ifndef THRUST_MSGS__MSG__DETAIL__THRUST__TRAITS_HPP_
#define THRUST_MSGS__MSG__DETAIL__THRUST__TRAITS_HPP_

#include "thrust_msgs/msg/detail/thrust__struct.hpp"
#include <stdint.h>
#include <rosidl_runtime_cpp/traits.hpp>
#include <sstream>
#include <string>
#include <type_traits>

// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__traits.hpp"

namespace rosidl_generator_traits
{

inline void to_yaml(
  const thrust_msgs::msg::Thrust & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: header
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "header:\n";
    to_yaml(msg.header, out, indentation + 2);
  }

  // member: thrust_meas
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "thrust_meas: ";
    value_to_yaml(msg.thrust_meas, out);
    out << "\n";
  }

  // member: thrust_comm
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "thrust_comm: ";
    value_to_yaml(msg.thrust_comm, out);
    out << "\n";
  }

  // member: thrust_comp
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "thrust_comp: ";
    value_to_yaml(msg.thrust_comp, out);
    out << "\n";
  }

  // member: alpha
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "alpha: ";
    value_to_yaml(msg.alpha, out);
    out << "\n";
  }

  // member: kp
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "kp: ";
    value_to_yaml(msg.kp, out);
    out << "\n";
  }

  // member: ki
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "ki: ";
    value_to_yaml(msg.ki, out);
    out << "\n";
  }

  // member: kd
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "kd: ";
    value_to_yaml(msg.kd, out);
    out << "\n";
  }

  // member: kff
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "kff: ";
    value_to_yaml(msg.kff, out);
    out << "\n";
  }

  // member: pulse
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "pulse: ";
    value_to_yaml(msg.pulse, out);
    out << "\n";
  }

  // member: mode
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "mode: ";
    value_to_yaml(msg.mode, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const thrust_msgs::msg::Thrust & msg)
{
  std::ostringstream out;
  to_yaml(msg, out);
  return out.str();
}

template<>
inline const char * data_type<thrust_msgs::msg::Thrust>()
{
  return "thrust_msgs::msg::Thrust";
}

template<>
inline const char * name<thrust_msgs::msg::Thrust>()
{
  return "thrust_msgs/msg/Thrust";
}

template<>
struct has_fixed_size<thrust_msgs::msg::Thrust>
  : std::integral_constant<bool, has_fixed_size<std_msgs::msg::Header>::value> {};

template<>
struct has_bounded_size<thrust_msgs::msg::Thrust>
  : std::integral_constant<bool, has_bounded_size<std_msgs::msg::Header>::value> {};

template<>
struct is_message<thrust_msgs::msg::Thrust>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // THRUST_MSGS__MSG__DETAIL__THRUST__TRAITS_HPP_
