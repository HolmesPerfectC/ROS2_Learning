#ifndef IMAGE_PUB_HPP_
#define IMAGE_PUB_HPP_


#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/image.hpp"
#include "cv_bridge/cv_bridge.h"
#include "opencv2/opencv.hpp"


namespace MYYOLO
{

class ImagePub : public rclcpp::Node
{
private:
    /* data */
    std::string image_pub_topic_name;
    std::string image_path;
    std::string video_path;
    int use_image_flag;
    std::string capture_format;
    rclcpp::TimerBase::SharedPtr image_timer_;
    rclcpp::TimerBase::SharedPtr video_timer_;
    cv::VideoCapture capture;
    int frame_num;
    int flag;

    rclcpp::Publisher<sensor_msgs::msg::Image>::SharedPtr image_pub_;

public:
    explicit ImagePub(const rclcpp::NodeOptions & options);
    void load_parameter();
    void video_capture();
    void image_timer_callback(); // if parameter use_image_flag = 1;
    void video_timer_callback(); // if parameter use_image_flag = 2;


};

} // namespace MYYOLO




#endif // IMAGE_IO_HPP_