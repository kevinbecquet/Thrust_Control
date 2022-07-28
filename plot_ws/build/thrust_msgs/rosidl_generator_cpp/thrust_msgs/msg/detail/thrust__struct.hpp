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
      this->thrust_meas = 0.0;
      this->thrust_comm = 0.0;
      this->thrust_comp = 0.0;
      this->alpha = 0.0;
      this->kp = 0.0;
      this->ki = 0.0;
      this->kd = 0.0;
      this->kff = 0.0;
      this->pulse = 0;
      this->mode = 0;
    }
  }

  explicit Thrust_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_alloc, _init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->thrust_meas = 0.0;
      this->thrust_comm = 0.0;
      this->thrust_comp = 0.0;
      this->alpha = 0.0;
      this->kp = 0.0;
      this->ki = 0.0;
      this->kd = 0.0;
      this->kff = 0.0;
      this->pulse = 0;
      this->mode = 0;
    }
  }

  // field types and members
  using _header_type =
    std_msgs::msg::Header_<ContainerAllocator>;
  _header_type header;
  using _thrust_meas_type =
    double;
  _thrust_meas_type thrust_meas;
  using _thrust_comm_type =
    double;
  _thrust_comm_type thrust_comm;
  using _thrust_comp_type =
    double;
  _thrust_comp_type thrust_comp;
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
  using _pulse_type =
    uint16_t;
  _pulse_type pulse;
  using _mode_type =
    uint16_t;
  _mode_type mode;

  // setters for named parameter idiom
  Type & set__header(
    const std_msgs::msg::Header_<ContainerAllocator> & _arg)
  {
    this->header = _arg;
    return *this;
  }
  Type & set__thrust_meas(
    const double & _arg)
  {
    this->thrust_meas = _arg;
    return *this;
  }
  Type & set__thrust_comm(
    const double & _arg)
  {
    this->thrust_comm = _arg;
    return *this;
  }
  Type & set__thrust_comp(
    const double & _arg)
  {
    this->thrust_comp = _arg;
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
  Type & set__pulse(
    const uint16_t & _arg)
  {
    this->pulse = _arg;
    return *this;
  }
  Type & set__mode(
    const uint16_t & _arg)
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
    if (this->thrust_meas != other.thrust_meas) {
      return false;
    }
    if (this->thrust_comm != other.thrust_comm) {
      return false;
    }
    if (this->thrust_comp != other.thrust_comp) {
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
    if (this->pulse != other.pulse) {
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
