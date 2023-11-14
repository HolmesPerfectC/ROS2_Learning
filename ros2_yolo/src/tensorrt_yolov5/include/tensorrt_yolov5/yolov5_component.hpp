#ifndef __TENSORRT_YOLOV5__YOLOV5_COMPONENT_HPP_
#define __TENSORRT_YOLOV5__YOLOV5_COMPONENT_HPP_

#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/image.hpp"
#include "vision_msgs/msg/bounding_box2_d_array.h"
#include "image_transport/image_transport.hpp"

namespace MYYOLO
{
class YoloComponent : public rclcpp::Node
{
private:
    /* data */
    rclcpp::Subscription<sensor_msgs::msg::Image>::SharedPtr image_sub_;
    image_transport::Subscriber raw_image_sub_;
    rclcpp::Publisher<vision_msgs__msg__BoundingBox2DArray>::SharedPtr obj_bboxes_pub_;
    rclcpp::Publisher<sensor_msgs::msg::Image>::SharedPtr obj_image_pub_;

    std::string image_sub_topic_name;
    image_transport::Publisher obj_image_pub;
public:
    explicit YoloComponent(const rclcpp::NodeOptions & options);
    ~YoloComponent();
    void load_parameters();
};


    
} // namespace MYYOLO



#endif // __TENSORRT_YOLOV5__YOLOV5_COMPONENT_HPP_

