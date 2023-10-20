#ifndef MY_COMPOSITION__MY_SERVER_COMPONENT_HPP_
#define MY_COMPOSITION__MY_SERVER_COMPONENT_HPP_

#include "my_composition/visibility_control.h"
#include "rclcpp/rclcpp.hpp"
#include "example_interfaces/srv/add_two_ints.hpp"


namespace my_composition
{
class MyServer : public rclcpp::Node
{
private:
    /* data */
    rclcpp::Service<example_interfaces::srv::AddTwoInts>::SharedPtr srv_;
public:
    MYCOMPOSITION_PUBLIC
    explicit MyServer(const rclcpp::NodeOptions & options);

};


} // namespace my_composition



#endif // MY_COMPOSITION__MY_SERVER_COMPONENT_HPP_