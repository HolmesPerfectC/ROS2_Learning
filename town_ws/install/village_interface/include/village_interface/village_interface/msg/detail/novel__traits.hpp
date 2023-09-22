// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from village_interface:msg/Novel.idl
// generated code does not contain a copyright notice

#ifndef VILLAGE_INTERFACE__MSG__DETAIL__NOVEL__TRAITS_HPP_
#define VILLAGE_INTERFACE__MSG__DETAIL__NOVEL__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "village_interface/msg/detail/novel__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'image'
#include "sensor_msgs/msg/detail/image__traits.hpp"

namespace village_interface
{

namespace msg
{

inline void to_flow_style_yaml(
  const Novel & msg,
  std::ostream & out)
{
  out << "{";
  // member: content
  {
    out << "content: ";
    rosidl_generator_traits::value_to_yaml(msg.content, out);
    out << ", ";
  }

  // member: image
  {
    out << "image: ";
    to_flow_style_yaml(msg.image, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const Novel & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: content
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "content: ";
    rosidl_generator_traits::value_to_yaml(msg.content, out);
    out << "\n";
  }

  // member: image
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "image:\n";
    to_block_style_yaml(msg.image, out, indentation + 2);
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const Novel & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace msg

}  // namespace village_interface

namespace rosidl_generator_traits
{

[[deprecated("use village_interface::msg::to_block_style_yaml() instead")]]
inline void to_yaml(
  const village_interface::msg::Novel & msg,
  std::ostream & out, size_t indentation = 0)
{
  village_interface::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use village_interface::msg::to_yaml() instead")]]
inline std::string to_yaml(const village_interface::msg::Novel & msg)
{
  return village_interface::msg::to_yaml(msg);
}

template<>
inline const char * data_type<village_interface::msg::Novel>()
{
  return "village_interface::msg::Novel";
}

template<>
inline const char * name<village_interface::msg::Novel>()
{
  return "village_interface/msg/Novel";
}

template<>
struct has_fixed_size<village_interface::msg::Novel>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<village_interface::msg::Novel>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<village_interface::msg::Novel>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // VILLAGE_INTERFACE__MSG__DETAIL__NOVEL__TRAITS_HPP_
