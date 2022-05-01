#include <ros/ros.h>
#include "control_barrel_world.h"

int main(int argc, char** argv)
{
  ros::init(argc, argv, "control_barrel_world_node");
  ros::NodeHandle nh; // get a handle to ROS

  carControl::car_control Thing;  // instatiate our class object

  ros::spin(); // check for new messages and call the callback if we get one

  return 0;
}