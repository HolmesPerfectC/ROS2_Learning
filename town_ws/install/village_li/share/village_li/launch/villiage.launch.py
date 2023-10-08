# 1. Import some package
from launch import LaunchDescription
from launch_ros.actions import Node

# 2. Define function
def generate_launch_description():
    # 3. Create Node Description
    li4_node = Node(package="village_li",
                    executable="li4_node",
                    parameters=[{'writer_timer_period': 5}]
                    )

    wang2_node = Node(package="village_wang", 
                      executable="wang2_node",
                      parameters=[{'novel_price': 5}]
                      )
    
    li4_node2 = Node(
        package="village_li",
        namespace="mirror_town",
        executable="li4_node",
        parameters=[{'writer_timer_period': 1}]
    )

    wang2_node2 = Node(
        package="village_wang",
        executable="wang2_node",
        namespace="mirror_town",
        parameters=[{'novel_price': 1}]
    )
    
    # 4. launch_description
    launch_d = LaunchDescription([li4_node, wang2_node, li4_node2, wang2_node2])
    return launch_d