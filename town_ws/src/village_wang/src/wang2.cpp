#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include "std_msgs/msg/u_int32.hpp"
#include "village_interface/srv/sell_novel.hpp"
#include <queue>


using std::placeholders::_1;
using std::placeholders::_2;

/*
    create a node class,named SingleDogNode, inherit rclcpp::Node
*/

class SingleNode : public rclcpp::Node
{
private:
    /* data */
    // Declaration for subscription 
    rclcpp::Subscription<std_msgs::msg::String>::SharedPtr sub_novel;

    // Declaration for publisher
    rclcpp::Publisher<std_msgs::msg::UInt32>::SharedPtr pub_money;

    std::queue<std::string> novels_queue;

    // Declaration for callbackgroup
    rclcpp::CallbackGroup::SharedPtr sell_novels_callback_group;

    // Declaration for server
    rclcpp::Service<village_interface::srv::SellNovel>::SharedPtr sell_server;

    unsigned int novel_price = 1;


    void novel_callback(const std_msgs::msg::String::SharedPtr novels)
    {
        std_msgs::msg::UInt32 money;
        money.data = 10;

        //publish money
        pub_money->publish(money);

        novels_queue.push(novels->data);

        RCLCPP_INFO(this->get_logger(), "I haved read %s.", novels->data.c_str());
    }

    void sell_novel_callback(const village_interface::srv::SellNovel::Request::SharedPtr request, 
                            const village_interface::srv::SellNovel::Response::SharedPtr response)
    {
        // if novels is not enough, wait for queue enough novels for sell
        RCLCPP_INFO(this->get_logger(), "Have Received buy book request, and he pay %d RMB! ", request->money);

        this->get_parameter("novel_price", novel_price);


        // Caculate novels chapter num that should return customer
        unsigned int num = int (request->money / novel_price);
        if (num > novels_queue.size())
        {
            // Wait for enough chapter for sell
            RCLCPP_INFO(this->get_logger(), "There don't have enough boook for sell, library has %ld book, and need %d books for sell", novels_queue.size(), num);

            rclcpp::Rate rate(1.0);
            while (novels_queue.size() < num)
            {
                RCLCPP_INFO(this->get_logger(), "Waiting for novel pub, current need %d chapter! ", int(num) - int(novels_queue.size()));
                rate.sleep();
            }

        }

        RCLCPP_INFO(this->get_logger(), "Now the library has %ld chapter novels, larger than num for sell %d", novels_queue.size(), num);

        // sell novel from book library
        for (int i = 0; i < (int)num; i++)
        {
            response->novels.push_back(novels_queue.front());
            novels_queue.pop();
        }
        
    }

public:
    SingleNode(std::string name) : Node(name)
    {
        RCLCPP_INFO(this->get_logger(), "Hello everybody!I'm SingleDog %s", name.c_str());

        //Create subscription
        sub_novel = this->create_subscription<std_msgs::msg::String>("sexy_girl", 10, std::bind(&SingleNode::novel_callback, this, _1));

        pub_money = this->create_publisher<std_msgs::msg::UInt32>("sexy_girl_money", 10);

        // Create sell_novel_callback_group
        sell_novels_callback_group = this->create_callback_group(rclcpp::CallbackGroupType::MutuallyExclusive);

        sell_server = this->create_service<village_interface::srv::SellNovel>("sell_novel", 
                                                                            std::bind(&SingleNode::sell_novel_callback, this, _1, _2), 
                                                                            rmw_qos_profile_services_default, 
                                                                            sell_novels_callback_group);

        this->declare_parameter<std::int64_t>("novel_price", novel_price);
    }
    

};




int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    /*create wang2 node*/
    auto node = std::make_shared<SingleNode>("wang2");

    // Create multithread executor
    rclcpp::executors::MultiThreadedExecutor executor;

    executor.add_node(node);
    executor.spin();

    // print a self introduction
    // RCLCPP_INFO(node->get_logger(), "Hello everybody, i'm Single Dog wang2! ");

    /*running node ,and detect signal for exit*/
    // rclcpp::spin(node);
    // rclcpp::shutdown();
    return 0;
}