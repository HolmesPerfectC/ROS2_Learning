import launch
from launch_ros.actions import ComposableNodeContainer
from launch_ros.descriptions import ComposableNode

def generate_launch_description():
    container = ComposableNodeContainer(
        name="tensorrt_yolo",
        namespace='',
        package='rclcpp_components',
        executable='component_container',
        composable_node_descriptions=[
            ComposableNode(
                package='raw_image_pub',
                plugin='MYYOLO::ImagePub',
                name='raw_image_pub',
                parameters=[{"image_pub_topic_name": "/camera/image_raw", 
                             "image_path": "/home/wuling/hpc/ros2_learn/ros2_yolo/data/test_image.jpg", 
                             "use_image_flag": 2, 
                             "video_path": "/home/wuling/hpc/ros2_learn/ros2_yolo/data/test_video.mp4"}]
            ),
            ComposableNode(
                package="tensorrt_yolov5",
                plugin='MYYOLO::YoloComponent',
                name="tensorrt_yolov5",
                parameters=[{"onnx_file": "/home/wuling/hpc/ros2_learn/ros2_yolo/src/tensorrt_yolov5/onnx/yolov5s.onnx", 
                            "engine_file": "/home/wuling/hpc/ros2_learn/ros2_yolo/data/yolov5s.engine", 
                            "label_file": "/home/wuling/hpc/ros2_learn/ros2_yolo/src/tensorrt_yolov5/config/coco.names", 
                            "colormap_filepath": "/home/wuling/hpc/ros2_learn/ros2_yolo/src/tensorrt_yolov5/config/coco_colormap.txt"
                            }]
            )
        ],
    )

    return launch.LaunchDescription([container])