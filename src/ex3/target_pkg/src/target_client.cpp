#include "rclcpp/rclcpp.hpp"
#include "check_target_int/srv/check_target.hpp"
#include <cmath>
#include <memory>
#include <chrono>
#include <string>

using namespace std::chrono_literals;

int main(int argc, char **argv)
{
rclcpp::init(argc, argv);

std::shared_ptr<rclcpp::Node> node = rclcpp::Node::make_shared("target_client");

auto client = node->create_client<check_target_int::srv::CheckTarget>("/check_target");

while (!client->wait_for_service(1s)) {
    if (!rclcpp::ok()) {
        RCLCPP_ERROR(rclcpp::get_logger("rclcpp"), "Interrupted while waiting for the service. Exiting.");
        return 0;}
    RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "service not available, waiting again...");}
RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Target Client Node is Ready");

double cur_x = 1.0, cur_y = 2.0, cur_z = 0.0; 
double tgt_x = 1.3, tgt_y = 2.4, tgt_z = 0.0; 
double tol = 0.6;

if (argc == 8)
{   cur_x = std::stod(argv[1]); 
    cur_y = std::stod(argv[2]); 
    cur_z = std::stod(argv[3]); 
    
    tgt_x = std::stod(argv[4]); 
    tgt_y = std::stod(argv[5]); 
    tgt_z = std::stod(argv[6]); 
    
    tol = std::stod(argv[7]); } 
else if (argc > 1) 
{   RCLCPP_WARN(node->get_logger(), "Usage: target_client <cur_x> <cur_y> <cur_z> <tgt_x> <tgt_y> <tgt_z> <tol>");
    RCLCPP_INFO(node->get_logger(), "Falling back to default coordinates."); }

//instantiating request pointer
auto request = std::make_shared<check_target_int::srv::CheckTarget::Request>();

//sending target position
request->target_position.x = tgt_x; 
request->target_position.y = tgt_y;
request->target_position.z = tgt_z;

//sending robot position
request->current_position.x = cur_x; 
request->current_position.y = cur_y;
request->current_position.z = cur_z;

//sending tolerance
request->tolerance = tol;

RCLCPP_INFO(node->get_logger(), "Sending Target Location: x[%f], y[%f], z[%f]", request->target_position.x, request->target_position.y, request->target_position.z);
RCLCPP_INFO(node->get_logger(), "Sending Robot Location: x[%f], y[%f], z[%f]",  request->current_position.x, request->current_position.y, request->current_position.z);
RCLCPP_INFO(node->get_logger(), "Sending Tolerance: %f", request->tolerance );

//sending request to get results back
auto result = client->async_send_request(request);

if (rclcpp::spin_until_future_complete(node, result) == rclcpp::FutureReturnCode::SUCCESS)
{   auto response = result.get();
    RCLCPP_INFO(node->get_logger(), "Distance: %f", response->distance);
    if (response->reached)
        {RCLCPP_INFO(node->get_logger(), "Target reached");}
    else{RCLCPP_INFO(node->get_logger(), "Target not reached");}}
else {
    RCLCPP_ERROR(node->get_logger(), "Failed to call service check_target");
}

rclcpp::shutdown();
return 0;
}