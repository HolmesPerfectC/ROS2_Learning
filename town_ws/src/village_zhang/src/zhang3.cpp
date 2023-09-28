#include "rclcpp/rclcpp.hpp"
#include "village_interface/srv/sell_novel.hpp"


using std::placeholders::_1;

class PoorManNode : public rclcpp::Node
{
private:
    /* data */

    rclcpp::Client<village_interface::srv::SellNovel>::SharedPtr novel_client;
    // receive result response function
    void novels_callback(rclcpp::Client<village_interface::srv::SellNovel>::SharedFuture response)
    {
        auto result = response.get();
        RCLCPP_INFO(this->get_logger(), " Haved received %ld chapter novels, now reading novels!", result->novels.size());

        for (std::string novel:result->novels)
        {
            RCLCPP_INFO(this->get_logger(), "%s", novel.c_str());
        }

        RCLCPP_INFO(this->get_logger(), "Finish reading novels, good!");
    }
public:
    //Init Function
    PoorManNode(std::string name) : Node(name)
    {
        RCLCPP_INFO(this->get_logger(), "Hello Every body! I'm poor king %s !", name.c_str());

        novel_client = this->create_client<village_interface::srv::SellNovel>("sell_novel");
    }
    
    // Request function
    void buy_novels()
    {
        RCLCPP_INFO(this->get_logger(), " To buy novels! ");

        while (!novel_client->wait_for_service(std::chrono::seconds(1)))
        {
            RCLCPP_INFO(this->get_logger(), "Wait sell novels service!....");
        }

        auto request = std::make_shared<village_interface::srv::SellNovel_Request>();
        request->money = 5;

        novel_client->async_send_request(request, std::bind(&PoorManNode::novels_callback, this, _1));
    }
    
};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);

    auto node = std::make_shared<PoorManNode>("zhang3");
    node->buy_novels();

    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;


}





