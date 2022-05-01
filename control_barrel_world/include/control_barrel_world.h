#ifndef CAR_CONTROL_H
#define CAR_CONTROL_H

#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <prius_msgs/Control.h>
#include <iomanip>
#include <vision_msgs/Detection2DArray.h>
#include <vision_msgs/Detection2D.h>
#include <vision_msgs/Detection3DArray.h>
#include <vision_msgs/Detection3D.h>
#include <vision_msgs/ObjectHypothesisWithPose.h>
#include <vision_msgs/ObjectHypothesisWithPose.h>

namespace carControl{


class car_control
{
public:
	car_control();
	void obstacle_detection (const vision_msgs::Detection3DArray& msgLidar);
	void person_detection (const vision_msgs::Detection2DArray& msgDetect);
	bool shutdown_car = false;

private:
	ros::NodeHandle nh_;
	ros::Publisher pub_;
	ros::Subscriber sub1_;
	ros::Subscriber sub2_;


};
}

#endif 