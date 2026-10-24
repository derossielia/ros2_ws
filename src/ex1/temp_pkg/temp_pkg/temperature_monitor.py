import rclpy
from rclpy.node import Node
from std_msgs.msg import Float64

class TemperatureMonitor(Node):
	def __init__(self):
		super().__init__('temperature_monitor')
		self.subscription=self.create_subscription(
			Float64,
			'/temperature',
			self.listener_callback,
			10)

	def listener_callback(self, msg):
		temp=msg.data
		self.get_logger().info(f'Received: {temp}°C')
		if temp > 25.0:
			self.get_logger().warn(f'WARNING: high temperature ({temp}°C)!')

def main(args=None):
	rclpy.init(args=args)
	node=TemperatureMonitor()
	rclpy.spin(node)
	node.destroy_node()
	rclpy.shutdown()

if __name__=='__main__':
	main()
