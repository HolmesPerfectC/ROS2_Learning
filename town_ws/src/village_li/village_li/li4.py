
#! /usr/bin/env python3
import rclpy
from rclpy.node import Node
from std_msgs.msg import String, UInt32

class WriterNode(Node):
    """
    Create a Wrieter Node, and out a string when initing.
    """
    def __init__(self, name):
        super().__init__(name)
        self.get_logger().info("Hello everybody! I'm %s, i'm a writer! " % name)
        self.pub_novel = self.create_publisher(String, "sexy_girl", 10)

        self.count = 0
        self.timer_period = 5
        self.timer = self.create_timer(self.timer_period, self.timer_callback)

        self.account = 80
        self.sub_money = self.create_subscription(UInt32, "sexy_girl_money", self.recv_money_callback, 10)

    def timer_callback(self):
        msg = String()
        msg.data = "第%d回：潋滟湖 %d 次偶遇胡艳娘" % (self.count,self.count)
        self.pub_novel.publish(msg)
        self.get_logger().info("Publised a chapter novel, context is: %s" % msg.data)
        self.count += 1


    def recv_money_callback(self, money):
        self.account += money.data
        self.get_logger().info("Received %d money of novel, The account haved %d money" % (money.data, self.account))


def main(args=None):
    """
    入口函数
    ros2运行该节点的入口函数
    编写ROS2节点的一般步骤
    1. 导入库文件
    2. 初始化客户端库
    3. 新建节点对象
    4. spin循环节点
    5. 关闭客户端库
    """
    rclpy.init(args=args)
    # li4_node = Node("li4")
    node = WriterNode("li4")
    # li4_node.get_logger().info("大家好，我是作家li4.")
    rclpy.spin(node)
    rclpy.shutdown()
