import rclpy
from rclpy.node import Node
from std_msgs.msg import String

class BaiPiaoNdoe(Node):
    
    def __init__(self, name):
        super().__init__(name)
        
        self.get_logger().info("Hello everybody! I'm BaiPiaoguai %s! " % name)
        sub_baipiao = self.create_subscription(String, "sexy_girl", self.baipiao_callback, 10)


    def baipiao_callback(self, str_novel):
        self.get_logger().info("Hahahah!I read %s for free!" % str_novel.data)

def main(args=None):
    rclpy.init(args=args)

    node = BaiPiaoNdoe("Li3")
    rclpy.spin(node)
    rclpy.shutdown()