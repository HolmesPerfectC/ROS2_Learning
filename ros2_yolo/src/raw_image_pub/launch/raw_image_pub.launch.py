import launch
from launch_ros.actions import ComposableNodeContainer
from launch_ros.descriptions import ComposableNode

def generate_launch_description():
    container = ComposableNodeContainer(
        name="image_pub_container",
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
                             "video_path": "/home/wuling/hpc/ros2_learn/ros2_yolo/data/fall_video.mp4"}]
            )
        ],
    )

    return launch.LaunchDescription([container])