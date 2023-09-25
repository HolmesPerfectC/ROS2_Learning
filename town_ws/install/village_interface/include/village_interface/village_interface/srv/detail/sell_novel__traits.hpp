// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from village_interface:srv/SellNovel.idl
// generated code does not contain a copyright notice

#ifndef VILLAGE_INTERFACE__SRV__DETAIL__SELL_NOVEL__TRAITS_HPP_
#define VILLAGE_INTERFACE__SRV__DETAIL__SELL_NOVEL__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "village_interface/srv/detail/sell_novel__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace village_interface
{

namespace srv
{

inline void to_flow_style_yaml(
  const SellNovel_Request & msg,
  std::ostream & out)
{
  out << "{";
  // member: money
  {
    out << "money: ";
    rosidl_generator_traits::value_to_yaml(msg.money, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const SellNovel_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: money
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "money: ";
    rosidl_generator_traits::value_to_yaml(msg.money, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const SellNovel_Request & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace srv

}  // namespace village_interface

namespace rosidl_generator_traits
{

[[deprecated("use village_interface::srv::to_block_style_yaml() instead")]]
inline void to_yaml(
  const village_interface::srv::SellNovel_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  village_interface::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use village_interface::srv::to_yaml() instead")]]
inline std::string to_yaml(const village_interface::srv::SellNovel_Request & msg)
{
  return village_interface::srv::to_yaml(msg);
}

template<>
inline const char * data_type<village_interface::srv::SellNovel_Request>()
{
  return "village_interface::srv::SellNovel_Request";
}

template<>
inline const char * name<village_interface::srv::SellNovel_Request>()
{
  return "village_interface/srv/SellNovel_Request";
}

template<>
struct has_fixed_size<village_interface::srv::SellNovel_Request>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<village_interface::srv::SellNovel_Request>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<village_interface::srv::SellNovel_Request>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace village_interface
{

namespace srv
{

inline void to_flow_style_yaml(
  const SellNovel_Response & msg,
  std::ostream & out)
{
  out << "{";
  // member: novels
  {
    if (msg.novels.size() == 0) {
      out << "novels: []";
    } else {
      out << "novels: [";
      size_t pending_items = msg.novels.size();
      for (auto item : msg.novels) {
        rosidl_generator_traits::value_to_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const SellNovel_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: novels
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.novels.size() == 0) {
      out << "novels: []\n";
    } else {
      out << "novels:\n";
      for (auto item : msg.novels) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        rosidl_generator_traits::value_to_yaml(item, out);
        out << "\n";
      }
    }
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const SellNovel_Response & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace srv

}  // namespace village_interface

namespace rosidl_generator_traits
{

[[deprecated("use village_interface::srv::to_block_style_yaml() instead")]]
inline void to_yaml(
  const village_interface::srv::SellNovel_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  village_interface::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use village_interface::srv::to_yaml() instead")]]
inline std::string to_yaml(const village_interface::srv::SellNovel_Response & msg)
{
  return village_interface::srv::to_yaml(msg);
}

template<>
inline const char * data_type<village_interface::srv::SellNovel_Response>()
{
  return "village_interface::srv::SellNovel_Response";
}

template<>
inline const char * name<village_interface::srv::SellNovel_Response>()
{
  return "village_interface/srv/SellNovel_Response";
}

template<>
struct has_fixed_size<village_interface::srv::SellNovel_Response>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<village_interface::srv::SellNovel_Response>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<village_interface::srv::SellNovel_Response>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<village_interface::srv::SellNovel>()
{
  return "village_interface::srv::SellNovel";
}

template<>
inline const char * name<village_interface::srv::SellNovel>()
{
  return "village_interface/srv/SellNovel";
}

template<>
struct has_fixed_size<village_interface::srv::SellNovel>
  : std::integral_constant<
    bool,
    has_fixed_size<village_interface::srv::SellNovel_Request>::value &&
    has_fixed_size<village_interface::srv::SellNovel_Response>::value
  >
{
};

template<>
struct has_bounded_size<village_interface::srv::SellNovel>
  : std::integral_constant<
    bool,
    has_bounded_size<village_interface::srv::SellNovel_Request>::value &&
    has_bounded_size<village_interface::srv::SellNovel_Response>::value
  >
{
};

template<>
struct is_service<village_interface::srv::SellNovel>
  : std::true_type
{
};

template<>
struct is_service_request<village_interface::srv::SellNovel_Request>
  : std::true_type
{
};

template<>
struct is_service_response<village_interface::srv::SellNovel_Response>
  : std::true_type
{
};

}  // namespace rosidl_generator_traits

#endif  // VILLAGE_INTERFACE__SRV__DETAIL__SELL_NOVEL__TRAITS_HPP_
