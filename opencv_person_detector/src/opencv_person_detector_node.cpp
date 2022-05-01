#include<ros/ros.h>
#include"opencv_person_detector.h"


int main(int argc, char **argv) {
ros::init(argc, argv, "opencv_person_detector");
ros::NodeHandle nh;

opencv_person_detector::OpenCVPersonDetector Thing;

ros::spin();

}