// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from thrust_msgs:msg/Thrust.idl
// generated code does not contain a copyright notice

#ifndef THRUST_MSGS__MSG__DETAIL__THRUST__BUILDER_HPP_
#define THRUST_MSGS__MSG__DETAIL__THRUST__BUILDER_HPP_

#include "thrust_msgs/msg/detail/thrust__struct.hpp"
#include <rosidl_runtime_cpp/message_initialization.hpp>
#include <algorithm>
#include <utility>


namespace thrust_msgs
{

namespace msg
{

namespace builder
{

class Init_Thrust_mode
{
public:
  explicit Init_Thrust_mode(::thrust_msgs::msg::Thrust & msg)
  : msg_(msg)
  {}
  ::thrust_msgs::msg::Thrust mode(::thrust_msgs::msg::Thrust::_mode_type arg)
  {
    msg_.mode = std::move(arg);
    return std::move(msg_);
  }

private:
  ::thrust_msgs::msg::Thrust msg_;
};

class Init_Thrust_kff
{
public:
  explicit Init_Thrust_kff(::thrust_msgs::msg::Thrust & msg)
  : msg_(msg)
  {}
  Init_Thrust_mode kff(::thrust_msgs::msg::Thrust::_kff_type arg)
  {
    msg_.kff = std::move(arg);
    return Init_Thrust_mode(msg_);
  }

private:
  ::thrust_msgs::msg::Thrust msg_;
};

class Init_Thrust_kd
{
public:
  explicit Init_Thrust_kd(::thrust_msgs::msg::Thrust & msg)
  : msg_(msg)
  {}
  Init_Thrust_kff kd(::thrust_msgs::msg::Thrust::_kd_type arg)
  {
    msg_.kd = std::move(arg);
    return Init_Thrust_kff(msg_);
  }

private:
  ::thrust_msgs::msg::Thrust msg_;
};

class Init_Thrust_ki
{
public:
  explicit Init_Thrust_ki(::thrust_msgs::msg::Thrust & msg)
  : msg_(msg)
  {}
  Init_Thrust_kd ki(::thrust_msgs::msg::Thrust::_ki_type arg)
  {
    msg_.ki = std::move(arg);
    return Init_Thrust_kd(msg_);
  }

private:
  ::thrust_msgs::msg::Thrust msg_;
};

class Init_Thrust_kp
{
public:
  explicit Init_Thrust_kp(::thrust_msgs::msg::Thrust & msg)
  : msg_(msg)
  {}
  Init_Thrust_ki kp(::thrust_msgs::msg::Thrust::_kp_type arg)
  {
    msg_.kp = std::move(arg);
    return Init_Thrust_ki(msg_);
  }

private:
  ::thrust_msgs::msg::Thrust msg_;
};

class Init_Thrust_alpha
{
public:
  explicit Init_Thrust_alpha(::thrust_msgs::msg::Thrust & msg)
  : msg_(msg)
  {}
  Init_Thrust_kp alpha(::thrust_msgs::msg::Thrust::_alpha_type arg)
  {
    msg_.alpha = std::move(arg);
    return Init_Thrust_kp(msg_);
  }

private:
  ::thrust_msgs::msg::Thrust msg_;
};

class Init_Thrust_thrust
{
public:
  explicit Init_Thrust_thrust(::thrust_msgs::msg::Thrust & msg)
  : msg_(msg)
  {}
  Init_Thrust_alpha thrust(::thrust_msgs::msg::Thrust::_thrust_type arg)
  {
    msg_.thrust = std::move(arg);
    return Init_Thrust_alpha(msg_);
  }

private:
  ::thrust_msgs::msg::Thrust msg_;
};

class Init_Thrust_header
{
public:
  Init_Thrust_header()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_Thrust_thrust header(::thrust_msgs::msg::Thrust::_header_type arg)
  {
    msg_.header = std::move(arg);
    return Init_Thrust_thrust(msg_);
  }

private:
  ::thrust_msgs::msg::Thrust msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::thrust_msgs::msg::Thrust>()
{
  return thrust_msgs::msg::builder::Init_Thrust_header();
}

}  // namespace thrust_msgs

#endif  // THRUST_MSGS__MSG__DETAIL__THRUST__BUILDER_HPP_
