#ifndef MY_COMPOSITION__MY_TALKER_COMPONENT_HPP_
#define MY_COMPOSITION__MY_TALKER_COMPONENT_HPP_
#include "my_composition/visibility_control.h"
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

namespace my_compositon
{

class MyTalker : public rclcpp::Node
{
private:
    /* data */
    rclcpp::Publisher<std_msgs::msg::String>::SharedPtr pub_;
    size_t count_;
    rclcpp::TimerBase::SharedPtr timer_;
    
protected:
    void on_timer();

public:
    MYCOMPOSITION_PUBLIC
    explicit MyTalker(const rclcpp::NodeOptions & options);

};



} // namespace my_composition
#endif // MY_COMPOSITION__MY_TALKER_COMPONENT_HPP_