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
    auto handle_add_two_ints = 
    [this](
        const std::shared_ptr<example_interfaces::srv::AddTwoInts::Request> request,
        std::shared_ptr<example_interfaces::srv::AddTwoInts::Response> response
        ) -> void
        {
            RCLCPP_INFO(
                this->get_logger(),"My server Incoming request: [a: %" PRId64 ", b: %" PRId64 "]",
                request->a, request->b);
            std::flush(std::cout);
            response->sum = request->a + request->b;
        };

    srv_ = create_service<example_interfaces::srv::AddTwoInts>("add_two_ints", handle_add_two_ints);
}
} // namespace my_composition

#include "rclcpp_components/register_node_macro.hpp"

RCLCPP_COMPONENTS_REGISTER_NODE(my_composition::MyServer)