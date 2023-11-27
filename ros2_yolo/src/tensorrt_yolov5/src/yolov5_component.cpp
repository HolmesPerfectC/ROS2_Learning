#include <iostream>
#include <fstream>
#include <vector>
#include <glob.h>
#include <map>

#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/image.hpp"
#include "opencv2/opencv.hpp"
#include "cv_bridge/cv_bridge.h"

#include "tensorrt_yolov5/yolov5_component.hpp"
#include "trt_yolo.hpp"


namespace 
{
std::vector<std::string> getFilePath(const std::string & input_dir)
{
  glob_t glob_buffer;
  std::vector<std::string> files;
  glob((input_dir + "*").c_str(), 0, NULL, &glob_buffer);
  for (size_t i = 0; i < glob_buffer.gl_pathc; i++) {
    files.push_back(glob_buffer.gl_pathv[i]);
  }
  globfree(&glob_buffer);
  return files;
}


} // namespace 

namespace MYYOLO
{

YoloComponent::YoloComponent(const rclcpp::NodeOptions &options)
 : Node("yolo_component", options) 
 {
    load_parameters();

    if (!read_colormap(color_map, colormap_filepath))
    {
      RCLCPP_INFO(this->get_logger(), "There is no colormap file! Creating coco colormap file...");
      if (!generate_colormap(color_map, colormap_filepath))
      {
         RCLCPP_INFO(this->get_logger(), "Failed created coco colormap file!");
      }
      RCLCPP_INFO(this->get_logger(), "Coco colormap file saved in %s ", colormap_filepath.c_str());
    }
    
    std::cout << mode << std::endl;
    std::cout << gpu_device_id << std::endl;
    std::cout << yolo_config_.iou_thresh << std::endl;
    if (!yolo::set_cuda_device(gpu_device_id))
    {
      RCLCPP_ERROR(this->get_logger(), "Given GPU not exist or suitable");
    }
    if (!readLabelFile(label_file, &labels_))
    {
      RCLCPP_ERROR(this->get_logger(), "Could not find label file! ");
    }
    std::ifstream fs(engine_file);
    const auto calibration_images = getFilePath(calib_image_directory);
    if (fs.is_open())
    {
      RCLCPP_INFO(this->get_logger(), "Found %s ", engine_file.c_str());
      net_ptr_.reset(new yolo::Net(engine_file, false));
      if (net_ptr_->getMaxBatchSize() != 1)
      {
         RCLCPP_INFO(this->get_logger(),
          " Max Batch size %d should be 1. Rebuild engine from file.",
          net_ptr_->getMaxBatchSize());
         net_ptr_.reset(new yolo::Net(onnx_file, mode, 1, yolo_config_, calibration_images, calib_cache_file));
         net_ptr_->save(engine_file);
      }
      
    }
    else
    {
      RCLCPP_INFO(this->get_logger(), 
      "Could not find %s engine file. Try makeing TensorRT engine from onnx.",
       engine_file.c_str());
      net_ptr_.reset(new yolo::Net(onnx_file, mode, 1, yolo_config_, calibration_images, calib_cache_file));
      net_ptr_->save(engine_file);
    }
    RCLCPP_INFO(this->get_logger(), "Inference engine prepared.");

    using std::chrono_literals::operator""ms;
    connect_timer_ = rclcpp::create_timer(this, get_clock(), 100ms, std::bind(&YoloComponent::connectCb, this));

    RCLCPP_INFO(this->get_logger(), "connect_timer created.");
    
    std::lock_guard<std::mutex> lock(connect_mutex_);
    obj_bboxes_pub_ = this->create_publisher<vision_msgs::msg::Detection2DArray>("out/objects", 1);
    obj_image_pub = image_transport::create_publisher(this, "out/image_objects");

    out_scores_ = std::make_unique<float[]>(net_ptr_->getMaxBatchSize() * net_ptr_->getMaxDetections());
    out_boxes_ = std::make_unique<float[]>(net_ptr_->getMaxBatchSize() * net_ptr_->getMaxDetections() * 4);
    out_classes_ = std::make_unique<float[]>(net_ptr_->getMaxBatchSize() * net_ptr_->getMaxDetections());


    

 }


void YoloComponent::load_parameters()
{
   onnx_file = this->declare_parameter("onnx_file", "/home/wuling/hpc/ros2_learn/ros2_yolo/src/tensorrt_yolov5/onnx/yolov5s.onnx");
   engine_file = this->declare_parameter("engine_file", "/home/wuling/hpc/ros2_learn/ros2_yolo/data/yolov5s.engine");
   label_file = this->declare_parameter("label_file", "/home/wuling/hpc/ros2_learn/ros2_yolo/src/tensorrt_yolov5/config/coco.names");
   colormap_filepath = this->declare_parameter("colormap_filepath", "/home/wuling/hpc/ros2_learn/ros2_yolo/src/tensorrt_yolov5/config/coco_colormap.txt");
   calib_image_directory = this->declare_parameter("calib_image_directory", "");
   calib_cache_file = this->declare_parameter("calib_cache_file", "");
   mode = this->declare_parameter("mode", "FP32");
   gpu_device_id = this->declare_parameter("gpu_id", 0);
   yolo_config_.num_anchors = this->declare_parameter("num_anchors", 3);
   anchors = this->declare_parameter("anchors", 
                                    std::vector<double>{10, 13, 16, 30, 33, 23, 30, 61, 62, 45, 59, 119, 116, 90, 156, 198, 373, 326});
   std::vector<float> anchors_float(anchors.begin(), anchors.end());
   yolo_config_.anchors = anchors_float;

   scale_x_y = this->declare_parameter("scale_x_y", std::vector<double>{1.0, 1.0, 1.0});
   std::vector<float> scale_x_y_float(scale_x_y.begin(), scale_x_y.end());
   yolo_config_.scale_x_y = scale_x_y_float;
   yolo_config_.score_thresh = this->declare_parameter("score_thresh", 0.1);
   yolo_config_.iou_thresh = this->declare_parameter("iou_thresh", 0.45);
   yolo_config_.detections_per_im = this->declare_parameter("detections_per_im", 100);
   yolo_config_.use_darknet_layer = this->declare_parameter("use_darknet_layer", false);
   yolo_config_.ignore_thresh = this->declare_parameter("ignore_thresh", 0.5);
}

bool YoloComponent::readLabelFile(const std::string &filepath, std::vector<std::string> *labels)
{
   std::ifstream labelsFile(filepath);
   if (!labelsFile.is_open())
   {
      RCLCPP_ERROR(this->get_logger(), "Could not open label file. [%s]", filepath.c_str());
      return false;
   }
   std::string label;
   while (getline(labelsFile, label))
   {
      labels->push_back(label);
   }
   return true;
   
}


void YoloComponent::connectCb()
{
   using std::placeholders:: _1;
   std::lock_guard<std::mutex> lock(connect_mutex_);
   if (obj_bboxes_pub_->get_subscription_count() == 0 && obj_image_pub.getNumSubscribers() == 0)
   {
      raw_image_sub_.shutdown();
   }
   else if (!raw_image_sub_)
   {
      raw_image_sub_ = image_transport::create_subscription(this, 
      "/camera/image_raw", 
      std::bind(&YoloComponent::callback, this, _1), 
      "raw", 
      rmw_qos_profile_sensor_data);
   }
}

void YoloComponent::callback(const sensor_msgs::msg::Image::ConstSharedPtr in_image_msg)
{
   vision_msgs::msg::Detection2DArray objections;
   if (!yolo::set_cuda_device(gpu_device_id))
   {
      RCLCPP_ERROR(this->get_logger(), "Given GPU not exist or suitable");
      return;
   }

   cv_bridge::CvImagePtr in_image_ptr;
   try
   {
      in_image_ptr = cv_bridge::toCvCopy(in_image_msg, sensor_msgs::image_encodings::BGR8);
   }
   catch(const std::exception& e)
   {
      RCLCPP_ERROR(this->get_logger(), "cv_bridge exception: %s", e.what());
      return;
   }
   if (!net_ptr_->detect(in_image_ptr->image, out_scores_.get(), out_boxes_.get(), out_classes_.get()))
   {
      RCLCPP_WARN(this->get_logger(), "Failed to inference!");
      return;
   }
   const auto width = in_image_ptr->image.cols;
   const auto height = in_image_ptr->image.rows;
   // std::cout << "width: " << width << "  height: " << height << std::endl;
   for (int i = 0; i < yolo_config_.detections_per_im; ++i)
   {
      if (out_scores_[i] < yolo_config_.ignore_thresh)
      {
         break;
      }
      vision_msgs::msg::Detection2D object;
      object.bbox.center.position.x = out_boxes_[4 * i] * width;
      object.bbox.center.position.y = out_boxes_[4 * i + 1] * height;
      object.bbox.size_x = out_boxes_[4 * i + 2] * width;
      object.bbox.size_y = out_boxes_[4 * i + 3] *height;
      vision_msgs::msg::ObjectHypothesisWithPose hypo;
      std::string out_class = std::to_string(out_classes_[i]);
      hypo.hypothesis.class_id = out_class;
      hypo.hypothesis.score = out_scores_[i];
      object.results.push_back(hypo);
      
      objections.detections.push_back(object);

      // std::cout << "x: " << object.bbox.center.position.x << "  y: " << object.bbox.center.position.y << std::endl;
      // std::cout << "size_x: " << object.bbox.size_x << "  size_y: " << object.bbox.size_y << std::endl;

      const auto left = std::max(0, static_cast<int>(object.bbox.center.position.x));
      const auto top = std::max(0, static_cast<int>(object.bbox.center.position.y));
      const auto right = std::min(static_cast<int>(object.bbox.center.position.x + object.bbox.size_x ), width);
      const auto bottom = std::min(static_cast<int>(object.bbox.center.position.y + object.bbox.size_y), height);
      

      cv::rectangle(in_image_ptr->image, cv::Point(left, top), cv::Point(right, bottom), color_map[out_classes_[i]], 3, 8, 0);
      cv::imwrite("/home/wuling/hpc/ros2_learn/ros2_yolo/data/anchor_test.jpg", in_image_ptr->image);
   }

   objections.header = in_image_msg->header;

   obj_image_pub.publish(in_image_ptr->toImageMsg());
   obj_bboxes_pub_->publish(objections);
   
   
}


bool YoloComponent::generate_colormap(std::map<float, cv::Scalar> &color_map, std::string &colormap_filepath)
{
   cv::RNG rng(cv::getTickCount());
   std::ofstream outFile(colormap_filepath);

   if (!outFile.is_open())
   {
      std::cerr << "Could not open colormap_file: " << colormap_filepath << std::endl;
      return false;
   }
   

   for (float key = 0.0f; key < 80.0f; key += 1.0f)
   {
      cv::Scalar randomScalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
      color_map[key] = randomScalar;
   }


   for (const auto& pair : color_map)
   {
      outFile  << pair.first << " " << pair.second[0] << " " << pair.second[1] << " " << pair.second[2] << " " << pair.second[3] << std::endl;
   }

   outFile.close();
   
   return true;
   
}

bool YoloComponent::read_colormap(std::map<float, cv::Scalar> &color_map, std::string &colormap_filepath)
{
   std::ifstream inFile(colormap_filepath);

   if (!inFile.is_open())
   {
      std::cerr << "Error opening colormap file: " << colormap_filepath << std::endl;
      return false;
   }
   float key;
   cv::Scalar value;
   while (inFile >> key >> value[0] >> value[1] >> value[2] >> value[3])
   {
      color_map[key] = value;
   }

   inFile.close();
   return true;
}

} // namespace MYYOLO

#include "rclcpp_components/register_node_macro.hpp"
RCLCPP_COMPONENTS_REGISTER_NODE(MYYOLO::YoloComponent)