#ifndef PCL_OBSTACLE_DETECTOR
#define PCL_OBSTACLE_DETECTOR

#include <ros/ros.h>
#include <sensor_msgs/PointCloud2.h> // needed to subscribe to the point cloud
#include <vision_msgs/Detection3DArray.h> // needed to publish

#include <iostream>
#include <pcl/ModelCoefficients.h>
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <pcl/sample_consensus/method_types.h>
#include <pcl/sample_consensus/model_types.h>
#include <pcl/segmentation/sac_segmentation.h>
#include <pcl_ros/transforms.h>
#include <pcl_conversions/pcl_conversions.h>
#include <pcl/common/common.h>
#include <pcl/filters/extract_indices.h>
#include <pcl/filters/voxel_grid.h>
#include <pcl/features/normal_3d.h>
#include <pcl/search/kdtree.h>
#include <pcl/segmentation/extract_clusters.h>
#include <pcl/common/centroid.h>

namespace pcl_obstacle_detector{


class PclObstacleDetector{
public:
	PclObstacleDetector();
	void Input_values(const sensor_msgs::PointCloud2& msgIn );

private:
	ros::NodeHandle nh_;
	ros::Publisher pub_;
	ros::Subscriber sub_;
};

}
#endif