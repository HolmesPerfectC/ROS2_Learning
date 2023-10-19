#include "my_composition/my_listener_component.hpp"

#include <iostream>
#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

namespace my_composition
{

// Create a Listener "component" that subclassed the generic rclcpp::Node base class.
// Components get built into shared libraries and as such do not write their own main functions.
// The process using the component's library will instantiate the class as a ROS node.
MyListener::MyListener(const rclcpp::NodeOptions & options)
 : Node("my_listener", options)
{
    // Create a callback function for when message are received.
    // Variations of this function exist using, for example, UniquePtr for zero-copy transport. 
    auto callback = 
        [this](std_msgs::msg::String::ConstSharedPtr msg) -> void
        {
            RCLCPP_INFO(this->get_logger(), "I heard: [%s]", msg->data.c_str());
            std::flush(std::cout);
        };

    // Create a subsription to the "chatter" topic which can be matched with one or more
    // compatible ROS publishers.
    // Note that not all publishers on the same topic with the same type will be compatible:
    // they must have compatible Quality of Service policies.

    sub_ = create_subscription<std_msgs::msg::String>("chatter", 10, callback);
}

} // namespace my_composition

#include "rclcpp_components/register_node_macro.hpp"

// Register the component with class_loader.
// This acts as a sort of entry point, allowing the component to be discoverable when its library
// is being loaded into a running process.
RCLCPP_COMPONENTS_REGISTER_NODE(my_composition::MyListener)