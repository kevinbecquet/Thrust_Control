// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from thrust_msgs:msg/Thrust.idl
// generated code does not contain a copyright notice

#ifndef THRUST_MSGS__MSG__DETAIL__THRUST__STRUCT_HPP_
#define THRUST_MSGS__MSG__DETAIL__THRUST__STRUCT_HPP_

#include <rosidl_runtime_cpp/bounded_vector.hpp>
#include <rosidl_runtime_cpp/message_initialization.hpp>
#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>


// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__thrust_msgs__msg__Thrust __attribute__((deprecated))
#else
# define DEPRECATED__thrust_msgs__msg__Thrust __declspec(deprecated)
#endif

namespace thrust_msgs
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct Thrust_
{
  using Type = Thrust_<ContainerAllocator>;

  explicit Thrust_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->thrust = 0.0;
      this->alpha = 0.0;
      this->kp = 0.0;
      this->ki = 0.0;
      this->kd = 0.0;
      this->kff = 0.0;
      this->mode = 0;
    }
  }

  explicit Thrust_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_alloc, _init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->thrust = 0.0;
      this->alpha = 0.0;
      this->kp = 0.0;
      this->ki = 0.0;
      this->kd = 0.0;
      this->kff = 0.0;
      this->mode = 0;
    }
  }

  // field types and members
  using _header_type =
    std_msgs::msg::Header_<ContainerAllocator>;
  _header_type header;
  using _thrust_type =
    double;
  _thrust_type thrust;
  using _alpha_type =
    double;
  _alpha_type alpha;
  using _kp_type =
    double;
  _kp_type kp;
  using _ki_type =
    double;
  _ki_type ki;
  using _kd_type =
    double;
  _kd_type kd;
  using _kff_type =
    double;
  _kff_type kff;
  using _mode_type =
    uint8_t;
  _mode_type mode;

  // setters for named parameter idiom
  Type & set__header(
    const std_msgs::msg::Header_<ContainerAllocator> & _arg)
  {
    this->header = _arg;
    return *this;
  }
  Type & set__thrust(
    const double & _arg)
  {
    this->thrust = _arg;
    return *this;
  }
  Type & set__alpha(
    const double & _arg)
  {
    this->alpha = _arg;
    return *this;
  }
  Type & set__kp(
    const double & _arg)
  {
    this->kp = _arg;
    return *this;
  }
  Type & set__ki(
    const double & _arg)
  {
    this->ki = _arg;
    return *this;
  }
  Type & set__kd(
    const double & _arg)
  {
    this->kd = _arg;
    return *this;
  }
  Type & set__kff(
    const double & _arg)
  {
    this->kff = _arg;
    return *this;
  }
  Type & set__mode(
    const uint8_t & _arg)
  {
    this->mode = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    thrust_msgs::msg::Thrust_<ContainerAllocator> *;
  using ConstRawPtr =
    const thrust_msgs::msg::Thrust_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<thrust_msgs::msg::Thrust_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<thrust_msgs::msg::Thrust_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      thrust_msgs::msg::Thrust_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<thrust_msgs::msg::Thrust_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      thrust_msgs::msg::Thrust_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<thrust_msgs::msg::Thrust_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<thrust_msgs::msg::Thrust_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<thrust_msgs::msg::Thrust_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__thrust_msgs__msg__Thrust
    std::shared_ptr<thrust_msgs::msg::Thrust_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__thrust_msgs__msg__Thrust
    std::shared_ptr<thrust_msgs::msg::Thrust_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const Thrust_ & other) const
  {
    if (this->header != other.header) {
      return false;
    }
    if (this->thrust != other.thrust) {
      return false;
    }
    if (this->alpha != other.alpha) {
      return false;
    }
    if (this->kp != other.kp) {
      return false;
    }
    if (this->ki != other.ki) {
      return false;
    }
    if (this->kd != other.kd) {
      return false;
    }
    if (this->kff != other.kff) {
      return false;
    }
    if (this->mode != other.mode) {
      return false;
    }
    return true;
  }
  bool operator!=(const Thrust_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct Thrust_

// alias to use template instance with default allocator
using Thrust =
  thrust_msgs::msg::Thrust_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace thrust_msgs

#endif  // THRUST_MSGS__MSG__DETAIL__THRUST__STRUCT_HPP_
