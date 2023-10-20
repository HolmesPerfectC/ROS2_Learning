#include "my_composition/my_server_component.hpp"

#include <cinttypes>
#include <iostream>
#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "example_interfaces/srv/add_two_ints.hpp"

namespace my_composition
{
MyServer::MyServer(const rclcpp::NodeOptions & options) : Node("myserver", options)
{

}
} // namespace my_composition