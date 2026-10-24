import rclpy
from rclpy.node import Node
from vacuum_int.msg import VacuumMsg

class RobotNode(Node):
	def __init__(self):
		super().__init__('robot') 					                #node name
		self.publisher_=self.create_publisher(VacuumMsg, '/charge_status', 10)	#publisher setup
		self.timer=self.create_timer(0.2, self.timer_callback)		#timer function setup
		self.battery_lvl=100.0							            #starting battery level variable
		self.room_id=1                                              #index to track rooms
		self.room=[                                                 #room id-name tuples
			(1, 'Robot Vision Lab'),
			(2, 'SSL Lab'),
			(3, 'Neurorobotics Lab'),
			(4, 'IAS-Lab'),
			(5, 'Autonomous Robotics Lab'),
			(1, 'Robot Vision Lab'),		# at the end of the battery, goes back to charge station
        ]

	def timer_callback(self):
		msg=VacuumMsg()
		self.current_tuple=self.room[self.room_id]
		msg.room_id=self.current_tuple[0]
		msg.room_name=self.current_tuple[1]
		msg.battery_level=self.battery_lvl
		self.publisher_.publish(msg)
		self.get_logger().info(f'Publishing: {self.battery_lvl}%, ID:{self.room[self.room_id]}')
		if self.battery_lvl<=17.0:
			self.get_logger().info(f'Battery is dead, heading to Charging Station')
		if self.battery_lvl==0.0:
			self.battery_lvl=100.0
		self.battery_lvl-=0.5
		self.room_id=int((self.battery_lvl-100.0)//16.7)%len(self.room) # // is the floor operator: divides two numbers and rounds down to the closest integer


def main(args=None):
	rclpy.init(args=args)
	node=RobotNode()
	rclpy.spin(node)	#enters node loop until cntrl+C is pressed, then it cleans it up
	node.destroy_node()
	rclpy.shutdown()

if __name__=='__main__':
	main()
