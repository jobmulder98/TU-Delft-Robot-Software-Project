#include"pcl_obstacle_detector.h"

int main(int argc, char **argv) {


// Initialize the ROS system and become a node.
ros::init(argc, argv, "obstacle_detector");
ros::NodeHandle nh;

pcl_obstacle_detector::PclObstacleDetector Thing;


// Let ROS take over.
ros::spin();


}
