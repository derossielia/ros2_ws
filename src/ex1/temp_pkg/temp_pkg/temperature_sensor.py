import rclpy
from rclpy.node import Node
from std_msgs.msg import Float64

class TemperatureSensor(Node):
	def __init__(self):
		super().__init__('temperature_sensor') 					#node name
		self.publisher_=self.create_publisher(Float64, '/temperature', 10)	#publisher setup
		self.timer=self.create_timer(1.0, self.timer_callback)		#timer function setup
		self.current_temp=20.0							#starting temperature variable

	def timer_callback(self):
		msg=Float64()
		msg.data=self.current_temp
		self.publisher_.publish(msg)
		self.get_logger().info(f'Publishing: {self.current_temp}°C')
		self.current_temp+=0.5

def main(args=None):
	rclpy.init(args=args)
	node=TemperatureSensor()
	rclpy.spin(node)	#enters node loop until cntrl+C is pressed, then it cleans it up
	node.destroy_node()
	rclpy.shutdown()

if __name__=='__main__':
	main()
