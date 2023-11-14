#include <iostream>

#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/image.hpp"
#include "opencv2/opencv.hpp"

#include "tensorrt_yolov5/yolov5_component.hpp"
#include "tensorrt_yolov5/yolov5.hpp"

namespace MYYOLO
{

YoloComponent::YoloComponent(const rclcpp::NodeOptions &options)
 : Node("yolo_component", options) 
 {
    load_parameters();
    

 }
    
} // namespace MYYOLO
