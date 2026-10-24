import rclpy
from rclpy.node import Node
from vacuum_int.msg import VacuumMsg

class ChargingStation(Node):
	def __init__(self):
		super().__init__('charging_station')
		self.subscription=self.create_subscription(
			VacuumMsg,
			'/charge_status',
			self.listener_callback,
			10)

	def listener_callback(self, msg):
		ID=msg.room_id
		room=msg.room_name
		chg=msg.battery_level
		self.get_logger().info(f'Received: {chg}%, ID:{ID}, name: {room}')
		if chg < 17.0:
		    self.get_logger().warn(f'WARNING: battery below {chg}%! Heading to Charging Station')

def main(args=None):
	rclpy.init(args=args)
	node=ChargingStation()
	rclpy.spin(node)
	node.destroy_node()
	rclpy.shutdown()

if __name__=='__main__':
	main()
