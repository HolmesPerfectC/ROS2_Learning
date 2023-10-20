#include "my_composition/my_talker_component.hpp"

#include <iostream>
#include <memory>
#include <chrono>
#include <utility>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include "rclcpp_components/register_node_macro.hpp"

using namespace std::chrono_literals;

namespace my_composition
{
MyTalker::MyTalker(const rclcpp::NodeOptions & options) 
: Node("my_talker", options), count_(0)
{
    pub_ = create_publisher<std_msgs::msg::String>("chatter", 10);

    timer_ = create_wall_timer(1s, std::bind(&MyTalker::on_timer, this));
}

void MyTalker::on_timer()
{
    auto msg = std::make_unique<std_msgs::msg::String>();
    msg->data = "MyTalker Hello World: " + std::to_string(++count_);
    RCLCPP_INFO(this->get_logger(), "Publishing: %s", msg->data.c_str());
    std::flush(std::cout);

    // Put the message into queue to be processed by the middleware.
    // This call is non-blocking
    pub_->publish(std::move(msg));
}
} // namespace my_composition

RCLCPP_COMPONENTS_REGISTER_NODE(my_composition::MyTalker)