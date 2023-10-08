# 1. Import some package
from launch import LaunchDescription
from launch_ros.actions import Node

# 2. Define function
def generate_launch_description():
    # 3. Create Node Description
    li4_node = Node(package="village_li",
                    executable="li4_node"
                    )

    wang2_node = Node(package="village_wang", 
                      executable="wang2_node"
                      )
    
    # 4. launch_description
    launch_d = LaunchDescription([li4_node, wang2_node])
    return launch_d