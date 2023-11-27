#include <iostream>

#include "raw_image_pub/imagepub.hpp"
#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/image.hpp"
#include "opencv2/opencv.hpp"



namespace MYYOLO
{

using namespace std::chrono_literals;

ImagePub::ImagePub(const rclcpp::NodeOptions &options)
 : Node("image_pub_node", options)
{
    load_parameter();
    image_pub_ = this->create_publisher<sensor_msgs::msg::Image>(image_pub_topic_name, 3);
    if (use_image_flag == 1)
    {
        image_timer_ = this->create_wall_timer(40ms, std::bind(&ImagePub::image_timer_callback, this));
    }
    else if (use_image_flag == 2)
    {
        video_capture();
        video_timer_ = this->create_wall_timer(40ms, std::bind(&ImagePub::video_timer_callback, this));
        
    }
    else{
        RCLCPP_ERROR(this->get_logger(), "There is no this use_image_flag");
    }
}

// 获取node parameter
void ImagePub::load_parameter()
{
    this->declare_parameter<std::string>("image_pub_topic_name", "/camera/image_raw");
    this->declare_parameter<std::string>("image_path", "/home/wuling/hpc/ros2_learn/ros2_yolo/data/test_image.jpg");
    this->declare_parameter<int8_t>("use_image_flag", 2);
    this->declare_parameter<std::string>("video_path", "/home/wuling/hpc/ros2_learn/ros2_yolo/data/test_video.mp4");




    image_pub_topic_name = this->get_parameter("image_pub_topic_name").as_string();
    image_path = this->get_parameter("image_path").as_string();
    use_image_flag = this->get_parameter("use_image_flag").as_int();
    video_path = this->get_parameter("video_path").as_string();

}
// 图像发布回调函数
void ImagePub::image_timer_callback()
{
    cv::Mat frame = cv::imread(image_path);

    if (!frame.empty())
    {
        sensor_msgs::msg::Image img_msg;
        cv_bridge::CvImage(std_msgs::msg::Header(), "bgr8", frame).toImageMsg(img_msg);
        img_msg.header.frame_id = "image_file";
        image_pub_->publish(img_msg);

    }

}
// 视频发布回调函数
void ImagePub::video_timer_callback()
{
    if (flag == frame_num)
    {
        cv::VideoCapture();
    }

    cv::Mat frame;
    capture.read(frame);
    if (!frame.empty())
    {
        sensor_msgs::msg::Image img_msg;
        cv_bridge::CvImage(std_msgs::msg::Header(), "bgr8", frame).toImageMsg(img_msg);
        img_msg.header.frame_id = "video";
        image_pub_->publish(img_msg);
    }
    flag++;
}

void ImagePub::video_capture()
{
    capture = cv::VideoCapture(video_path);
    frame_num = capture.get(cv::CAP_PROP_FRAME_COUNT);
    flag = 0;
    RCLCPP_INFO(this->get_logger(), "the video total frame number is : %d", frame_num);
}

} // namespace MYYOLO

#include "rclcpp_components/register_node_macro.hpp"
RCLCPP_COMPONENTS_REGISTER_NODE(MYYOLO::ImagePub)