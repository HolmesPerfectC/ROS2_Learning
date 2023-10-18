#include "my_composition/my_node_like_listener_component.hpp"

#include <iostream>
#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

namespace my_composition
{

// Create a Listener "component" that does not subclass the gneric rclcpp::Node base class.
/**
 * Note that "component" don't have to derive from rclcpp::Node
 * In the case that an object does not inherit from rclcpp::Node, then it must implement:
 * - Constructor that takes `comst rclcpp::NodeOption&`
 * - get_node_base_interface() which returns a NodeBaseInterface::ShardPtr
 * 
 * This is an example of an object that implements the interface required to be a component.
*/

MyNodeLikeListener::MyNodeLikeListener(const rclcpp::NodeOptions & options) 
: node_(std::make_shared<rclcpp::Node>("my_listener", options))
{
    // Create a callback function for when message are received.
    // Variations of this function also exist using, for example, UniquePtr for zero-copy transport.
    auto callback = 
    [this](std_msgs::msg::String::ConstSharedPtr msg) -> void
    {
        RCLCPP_INFO(this->node_->get_logger(), "My_composition I herad: [%s]", msg->data.c_str());
        std::flush(std::cout);
    };

    // Create a subscription to the "chatter" topic which can be matched with one or more
    // compatible ROS publisher.
    // Note that not all publisher on the same topic with the same type will be compatible:
    // they must have compatible Quality of Service policies.
    sub_ = this->node_->create_subscription<std_msgs::msg::String>("chatter", 10, callback);
}

rclcpp::node_interfaces::NodeBaseInterface::SharedPtr
MyNodeLikeListener::get_node_base_interface() const
{
    return this->node_->get_node_base_interface();
}

} // namespace composition

#include "rclcpp_components/register_node_macro.hpp"

// Register the component with class_loader .
// This acts as a sort of entry point, allowing the component to be discoverable when its library
// is being loaded into a running process.
RCLCPP_COMPONENTS_REGISTER_NODE(my_composition::MyNodeLikeListener)