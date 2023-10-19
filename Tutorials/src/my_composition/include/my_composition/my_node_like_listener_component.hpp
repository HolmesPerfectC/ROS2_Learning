#ifndef COMPOSITION_NODE_LIKE_LISTENER_COMPONENT_HPP_
#define COMPOSITION_NODE_LIKE_LISTENER_COMPONENT_HPP_

#include "my_composition/visibility_control.h"
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

namespace my_composition
{

class MyNodeLikeListener
{
private:
    /* data */
    rclcpp::Node::SharedPtr node_;
    rclcpp::Subscription<std_msgs::msg::String>::SharedPtr sub_;
public:
    MYCOMPOSITION_PUBLIC
    explicit MyNodeLikeListener(const rclcpp::NodeOptions & options);

    MYCOMPOSITION_PUBLIC
    rclcpp::node_interfaces::NodeBaseInterface::SharedPtr 
    get_node_base_interface() const;
};




} //namespace composition

#endif //COMPOSITION__NODE_LIKE_LISTENER_COMPONENT_HPP_