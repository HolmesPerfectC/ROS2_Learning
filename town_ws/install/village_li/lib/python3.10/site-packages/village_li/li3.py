import rclpy
from rclpy.node import Node
from std_msgs.msg import String
from village_interface.srv import BorrowMoney

class BaiPiaoNdoe(Node):
    
    def __init__(self, name):
        super().__init__(name)
        
        self.get_logger().info("Hello everybody! I'm BaiPiaoguai %s! I'm so exciting! " % name)
        self.sub_baipiao = self.create_subscription(String, "sexy_girl", self.baipiao_callback, 10)

        self.borrow_client = self.create_client(BorrowMoney, "borrow_money")


    def baipiao_callback(self, str_novel):
        self.get_logger().info("Hahahah!I read %s for free!" % str_novel.data)

    def borrow_money_eat(self, money=10):
        self.get_logger().info("Borrow money for malatang! Need %d money" % money)
        while not self.borrow_client.wait_for_service(1.0):
            self.get_logger().warn("Service is't online! I'm waiting.... ")

        request = BorrowMoney.Request()
        request.name = self.get_name()
        request.money = money

        self.borrow_client.call_async(request).add_done_callback(self.borrow_response_callback)

    def borrow_response_callback(self, response):

        result = response.result()
        if result.success:
            self.get_logger().info("Have borrowed %d money to eat malatang! " % result.money)
        else:
            self.get_logger().info("Too mean! ")

def main(args=None):
    rclpy.init(args=args)

    node = BaiPiaoNdoe("Li3")
    node.borrow_money_eat()
    rclpy.spin(node)
    rclpy.shutdown()