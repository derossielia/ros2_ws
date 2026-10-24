#include "rclcpp/rclcpp.hpp"
#include "check_target_int/srv/CheckTarget.hpp"
#include <cmath>
#include <memory>

void distance(const check_target_int::srv::CheckTarget::Request request,
                    check_target_int::srv::CheckTarget::Response response)
{
  double dist_x = request->target_position.x - request->current_position.x;
  double dist_y = request->target_position.y - request->current_position.y;
  double dist_z = request->target_position.z - request->current_position.z;
  
  response->distance = std::sqrt((dist_x*dist_x)+(dist_y*dist_y)+(dist_z*dist_z));

  response->reached=(dist <= request->tolerance);
  
  RCLCPP_INFO(rclcpp::get_logger("rclcpp"), 
  "Calculated Distance: %.2fm | Reached: %s", 
  dist, response-&gt;reached ? "true" : "false");
}

int main(int argc, char **argv)
{
  rclcpp::init(argc, argv);

  std::shared_ptr<rclcpp::Node> node = rclcpp::Node::make_shared("add_two_ints_server");

  rclcpp::Service<example_interfaces::srv::AddTwoInts>::SharedPtr service =
    node->create_service<example_interfaces::srv::AddTwoInts>("add_two_ints", &add);

  RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Ready to add two ints.");

  rclcpp::spin(node);
  rclcpp::shutdown();
}