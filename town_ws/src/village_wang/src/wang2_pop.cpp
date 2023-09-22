#include "rclcpp/rclcpp.hpp"

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    /*create wang2 node*/
    auto node = std::make_shared<rclcpp::Node>("wang2");

    //print a self introduction
    RCLCPP_INFO(node->get_logger(), "Hello everybody, i'm Single Dog wang2! ");

    /*running node ,and detect signal for exit*/
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}