#ifndef __TENSORRT_YOLOV5__YOLOV5_COMPONENT_HPP_
#define __TENSORRT_YOLOV5__YOLOV5_COMPONENT_HPP_

#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/image.hpp"
#include "vision_msgs/msg/bounding_box2_d_array.h"
#include "vision_msgs/msg/detection2_d_array.hpp"
#include "image_transport/image_transport.hpp"
#include "trt_yolo.hpp"

namespace MYYOLO
{
class YoloComponent : public rclcpp::Node
{
private:
    /* data */
    rclcpp::Subscription<sensor_msgs::msg::Image>::SharedPtr image_sub_;
    image_transport::Subscriber raw_image_sub_;
    rclcpp::Publisher<vision_msgs::msg::Detection2DArray>::SharedPtr obj_bboxes_pub_;
    rclcpp::Publisher<sensor_msgs::msg::Image>::SharedPtr obj_image_pub_;
    image_transport::Publisher obj_image_pub;

    std::string image_sub_topic_name;

    std::mutex connect_mutex_;
    rclcpp::TimerBase::SharedPtr connect_timer_;
    std::string colormap_filepath;
    std::map<float, cv::Scalar> color_map;
    std::string onnx_file;
    std::string engine_file;
    std::string label_file;
    std::string calib_image_directory;
    std::string calib_cache_file;
    std::string mode;
    int gpu_device_id;
    yolo::Config yolo_config_;
    std::vector<double> anchors;
    std::vector<double> scale_x_y;

    std::vector<std::string> labels_;
    std::unique_ptr<float[]> out_scores_;
    std::unique_ptr<float[]> out_boxes_;
    std::unique_ptr<float[]> out_classes_;
    std::unique_ptr<yolo::Net> net_ptr_;
    

public:
    explicit YoloComponent(const rclcpp::NodeOptions & options);
    void load_parameters();
    void connectCb();
    void callback(const sensor_msgs::msg::Image::ConstSharedPtr image_msg);
    bool readLabelFile(const std::string &filepath, std::vector<std::string> * labels);
    bool generate_colormap(std::map<float, cv::Scalar> &color_map, std::string &colormap_filepath);
    bool read_colormap(std::map<float, cv::Scalar> &color_map, std::string &colormap_filepath);
};


    
} // namespace MYYOLO



#endif // __TENSORRT_YOLOV5__YOLOV5_COMPONENT_HPP_

