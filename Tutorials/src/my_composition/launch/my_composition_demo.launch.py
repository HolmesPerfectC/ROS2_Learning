"""Launch a talker and listener component in a component container"""
import launch
from launch_ros.actions import ComposableNodeContainer
from launch_ros.descriptions import ComposableNode

def generate_launch_description():
    """Generate launch description with multiple components."""
    container = ComposableNodeContainer(
        name="my_launch_container",
        namespace='',
        package='rclcpp_components',
        executable='component_container',
        composable_node_descriptions=[
            ComposableNode(
                package='my_composition',
                plugin='my_composition::MyTalker',
                name='mylaunchtalker'
            ),
            ComposableNode(
                package='my_composition',
                plugin='my_composition::MyListener',
                name='mylaunchlistener'
            )
        ],
        output='screen',
    )
    return launch.LaunchDescription([container])