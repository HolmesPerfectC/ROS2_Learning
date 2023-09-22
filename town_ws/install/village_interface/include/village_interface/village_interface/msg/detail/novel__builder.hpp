// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from village_interface:msg/Novel.idl
// generated code does not contain a copyright notice

#ifndef VILLAGE_INTERFACE__MSG__DETAIL__NOVEL__BUILDER_HPP_
#define VILLAGE_INTERFACE__MSG__DETAIL__NOVEL__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "village_interface/msg/detail/novel__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace village_interface
{

namespace msg
{

namespace builder
{

class Init_Novel_image
{
public:
  explicit Init_Novel_image(::village_interface::msg::Novel & msg)
  : msg_(msg)
  {}
  ::village_interface::msg::Novel image(::village_interface::msg::Novel::_image_type arg)
  {
    msg_.image = std::move(arg);
    return std::move(msg_);
  }

private:
  ::village_interface::msg::Novel msg_;
};

class Init_Novel_content
{
public:
  Init_Novel_content()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_Novel_image content(::village_interface::msg::Novel::_content_type arg)
  {
    msg_.content = std::move(arg);
    return Init_Novel_image(msg_);
  }

private:
  ::village_interface::msg::Novel msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::village_interface::msg::Novel>()
{
  return village_interface::msg::builder::Init_Novel_content();
}

}  // namespace village_interface

#endif  // VILLAGE_INTERFACE__MSG__DETAIL__NOVEL__BUILDER_HPP_
