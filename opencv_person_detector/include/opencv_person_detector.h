#ifndef OPENCV_PERSON_DETECTOR_H
#define OPENCV_PERSON_DETECTOR_H

#include <ros/ros.h>
#include <sensor_msgs/Image.h>
#include <iomanip>
#include <image_transport/image_transport.h>
#include <opencv2/opencv.hpp>
#include <cv_bridge/cv_bridge.h>
#include <vision_msgs/Detection2DArray.h>
#include <vision_msgs/Detection2D.h>
#include <vision_msgs/ObjectHypothesisWithPose.h>
#include <vision_msgs/ObjectHypothesisWithPose.h>
using namespace cv;
using namespace std;

namespace opencv_person_detector{

	class OpenCVPersonDetector{

		ros::Publisher detections_pub_;
		image_transport::Publisher visualPtr_;
		image_transport::Subscriber sub_;
		ros::NodeHandle nh_;
		



		private:
			
		public: 
			void detectAndDraw(const sensor_msgs::ImageConstPtr& msg);
			OpenCVPersonDetector();

	};
}

#endif

