#include "rclcpp/rclcpp.hpp"
#include "check_target_int/srv/check_target.hpp"
#include <cmath>
#include <memory>

void check_target_callback(const std::shared_ptr<check_target_int::srv::CheckTarget::Request> request,
                    std::shared_ptr<check_target_int::srv::CheckTarget::Response> response)
{
  double dist_x = request->target_position.x - request->current_position.x;
  double dist_y = request->target_position.y - request->current_position.y;
  double dist_z = request->target_position.z - request->current_position.z;
  
  float dist = std::sqrt((dist_x*dist_x)+(dist_y*dist_y)+(dist_z*dist_z));

  response->distance=dist;
  response->reached=(dist <= request->tolerance);
  
  RCLCPP_INFO(rclcpp::get_logger("rclcpp"), 
  "Calculated Distance: %.2fm | Reached: %s", 
  dist, response->reached ? "true" : "false");
}

int main(int argc, char **argv)
{
  rclcpp::init(argc, argv);

  std::shared_ptr<rclcpp::Node> node = rclcpp::Node::make_shared("target_server");

  rclcpp::Service<check_target_int::srv::CheckTarget>::SharedPtr service =
    node->create_service<check_target_int::srv::CheckTarget>("/check_target", &check_target_callback);

  RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Target Server Node is Ready");

  rclcpp::spin(node);
  rclcpp::shutdown();
  return 0;
}