#ifndef MY_COMPOSITION__MY_LISTENER_COMPONENT_HPP_
#define MY_COMPOSITION__MY_LISTENER_COMPONENT_HPP_

#include "my_composition/visibility_control.h"
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

namespace my_composition
{

class MyListener : public rclcpp::Node
{
private:
    /* data */
    rclcpp::Subscription<std_msgs::msg::String>::SharedPtr sub_;
public:
    MYCOMPOSITION_PUBLIC
    explicit MyListener(const rclcpp::NodeOptions & options);
};


} // namespace MyListener


#endif //MY_COMPOSITION__MY_LISTENER_COMPONENT_HPP_