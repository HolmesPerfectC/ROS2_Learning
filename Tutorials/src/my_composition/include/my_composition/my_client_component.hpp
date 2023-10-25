#ifndef MY_COMPOSITION__MY_CLINET_COMPONENT_HPP_
#define MY_COMPOSITION__MY_CLINET_COMPONENT_HPP_


#include "example_interfaces/srv/add_two_ints.hpp"
#include "rclcpp/rclcpp.hpp"

namespace my_composition
{
class MyClient : public rclcpp::Node
{
private:
    /* data */
    rclcpp::Client<example_interfaces::srv::AddTwoInts>::SharedPtr clinet_;
    rclcpp::TimerBase::SharedPtr timer_;
public:
    explicit MyClient(const rclcpp::NodeOptions & options);

protected:
    void on_timer();

};




} // namespace my_composition


#endif // MY_COMPOSITION__MY_CLINET_COMPONENT_HPP_


