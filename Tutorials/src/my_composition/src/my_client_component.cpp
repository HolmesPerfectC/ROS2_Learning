#include "my_composition/my_client_component.hpp"

#include <cinttypes>
#include <iostream>
#include <memory>

#include "example_interfaces/srv/add_two_ints.hpp"
#include "rclcpp/rclcpp.hpp"

using namespace std::chrono_literals;

namespace my_composition
{

MyClient::MyClient(const rclcpp::NodeOptions & options)
 : Node("myclient", options)
{
    clinet_ = create_client<example_interfaces::srv::AddTwoInts>("add_two_ints");
    timer_ = create_wall_timer(2s, std::bind(&MyClient::on_timer, this));
}

void MyClient::on_timer()
{
    if(!clinet_->wait_for_service(1s)){
        if(!rclcpp::ok()){
            RCLCPP_ERROR(
                this->get_logger(),
                "Interrupted while waiting for the service. Exiting."
            );
            return;
        }
        RCLCPP_INFO(this->get_logger(), "MyService not available after waiting");
        return;
    }

    auto request = std::make_shared<example_interfaces::srv::AddTwoInts::Request>();
    request->a = 2;
    request->b = 3;

    // 为了等待响应的到来，我们需要调用spin()函数。
    // 然而，该函数已经从另一个spin()函数内部调用。
    // 不幸的是，当前版本的spin()函数不是递归的，所以我们不能从另一个spin()函数内部调用spin()。
    // 因此，在这个回调中，我们不能等待我们刚刚发出的请求的响应，因为它是由其他spin函数执行的。
    // 解决这个问题的方法是给async_send_request()方法添加另一个参数，这个参数是一个回调函数，一旦future准备就绪就会被执行。
    // 然后我们从这个回调中返回，以便现有的spin()函数可以继续运行，我们的回调将在收到响应时被调用。
    using ServiceResponseFuture = rclcpp::Client<example_interfaces::srv::AddTwoInts>::SharedFuture;
    auto response_received_callback = [this](ServiceResponseFuture future){
        RCLCPP_INFO(this->get_logger(), "Got result: [%" PRId64 "]", future.get()->sum);
    };
    auto future_result = clinet_->async_send_request(request, response_received_callback);
}
} // namespace my_composition

#include "rclcpp_components/register_node_macro.hpp"

RCLCPP_COMPONENTS_REGISTER_NODE(my_composition::MyClient)