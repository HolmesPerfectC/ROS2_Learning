#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include "std_msgs/msg/u_int32.hpp"


using std::placeholders::_1;
using std::placeholders::_2;

/*
    create a node class,named SingleDogNode, inherit rclcpp::Node
*/

class SingleNode : public rclcpp::Node
{
private:
    /* data */
    //Declaration for subscription 
    rclcpp::Subscription<std_msgs::msg::String>::SharedPtr sub_novel;

    //Declaration for publisher
    rclcpp::Publisher<std_msgs::msg::UInt32>::SharedPtr pub_money;

    void novel_callback(const std_msgs::msg::String::SharedPtr novels)
    {
        std_msgs::msg::UInt32 money;
        money.data = 10;

        //publish money
        pub_money->publish(money);

        RCLCPP_INFO(this->get_logger(), "I haved read %s.", novels->data.c_str());
    }
public:
    SingleNode(std::string name) : Node(name)
    {
        RCLCPP_INFO(this->get_logger(), "Hello everybody!I'm SingleDog %s", name.c_str());

        //Create subscription
        sub_novel = this->create_subscription<std_msgs::msg::String>("sexy_girl", 10, std::bind(&SingleNode::novel_callback, this, _1));

        pub_money = this->create_publisher<std_msgs::msg::UInt32>("sexy_girl_money", 10);
    }
    

};




int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    /*create wang2 node*/
    auto node = std::make_shared<SingleNode>("wang2");

    //print a self introduction
    // RCLCPP_INFO(node->get_logger(), "Hello everybody, i'm Single Dog wang2! ");

    /*running node ,and detect signal for exit*/
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}