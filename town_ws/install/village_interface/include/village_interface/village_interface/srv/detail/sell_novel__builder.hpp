// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from village_interface:srv/SellNovel.idl
// generated code does not contain a copyright notice

#ifndef VILLAGE_INTERFACE__SRV__DETAIL__SELL_NOVEL__BUILDER_HPP_
#define VILLAGE_INTERFACE__SRV__DETAIL__SELL_NOVEL__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "village_interface/srv/detail/sell_novel__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace village_interface
{

namespace srv
{

namespace builder
{

class Init_SellNovel_Request_money
{
public:
  Init_SellNovel_Request_money()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::village_interface::srv::SellNovel_Request money(::village_interface::srv::SellNovel_Request::_money_type arg)
  {
    msg_.money = std::move(arg);
    return std::move(msg_);
  }

private:
  ::village_interface::srv::SellNovel_Request msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::village_interface::srv::SellNovel_Request>()
{
  return village_interface::srv::builder::Init_SellNovel_Request_money();
}

}  // namespace village_interface


namespace village_interface
{

namespace srv
{

namespace builder
{

class Init_SellNovel_Response_novels
{
public:
  Init_SellNovel_Response_novels()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::village_interface::srv::SellNovel_Response novels(::village_interface::srv::SellNovel_Response::_novels_type arg)
  {
    msg_.novels = std::move(arg);
    return std::move(msg_);
  }

private:
  ::village_interface::srv::SellNovel_Response msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::village_interface::srv::SellNovel_Response>()
{
  return village_interface::srv::builder::Init_SellNovel_Response_novels();
}

}  // namespace village_interface

#endif  // VILLAGE_INTERFACE__SRV__DETAIL__SELL_NOVEL__BUILDER_HPP_
