
#include"pcl_obstacle_detector.h"

//typedef pcl::PointCloud<pcl::PointXYZ> PointCloud;
//using namespace sensor_msgs;
namespace pcl_obstacle_detector{


PclObstacleDetector::PclObstacleDetector(){
		// Create a publisher object.
	pub_ = nh_.advertise<vision_msgs::Detection3DArray>( "pcl_obstacle_detector_node/detections", 1);

	// Create a subscriber object .
	sub_ = nh_.subscribe("point_cloud", 1,   &PclObstacleDetector::Input_values, this);

}

void PclObstacleDetector::Input_values(const sensor_msgs::PointCloud2& msgIn ){
	

	pcl::PointCloud<pcl::PointXYZ>::Ptr cloud (new pcl::PointCloud<pcl::PointXYZ>), cloud_f (new pcl::PointCloud<pcl::PointXYZ>), cloud_plane(new pcl::PointCloud<pcl::PointXYZ>);
	pcl::fromROSMsg(msgIn, *cloud);

	pcl::ModelCoefficients::Ptr coefficients (new pcl::ModelCoefficients);
	pcl::PointIndices::Ptr inliers (new pcl::PointIndices);


	// Create the filtering object
	// Create the filtering object: downsample the dataset using a leaf size of 1cm
	pcl::VoxelGrid<pcl::PointXYZ> vg;
	pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_filtered (new pcl::PointCloud<pcl::PointXYZ>);
	vg.setInputCloud (cloud);
	vg.setLeafSize (0.01f, 0.01f, 0.01f);
	vg.filter (*cloud_filtered);
	std::cout << "PointCloud after filtering has: " << cloud_filtered->size ()  << " data points." << std::endl; //*


	// Create the segmentation object
	pcl::SACSegmentation<pcl::PointXYZ> seg;
	// Optional
	seg.setOptimizeCoefficients (true);
	// Mandatory
	seg.setModelType (pcl::SACMODEL_PLANE);
	seg.setMethodType (pcl::SAC_RANSAC);
	seg.setDistanceThreshold (0.3); //30cm

	seg.setInputCloud (cloud);
  	seg.segment (*inliers, *coefficients);

	

    pcl::ExtractIndices<pcl::PointXYZ> extract;
    extract.setInputCloud (cloud_filtered);
    extract.setIndices (inliers);
    extract.setNegative (false);

    extract.filter (*cloud_plane);
    std::cout << "PointCloud representing the planar component: " << cloud_plane->size () << " data points." << std::endl;

    // Remove the planar inliers, extract the rest
    extract.setNegative (true);
    extract.filter (*cloud_f);
    *cloud_filtered = *cloud_f;


	pcl::search::KdTree<pcl::PointXYZ>::Ptr tree (new pcl::search::KdTree<pcl::PointXYZ>);
	tree->setInputCloud (cloud_filtered);

	std::vector<pcl::PointIndices> cluster_indices;
	pcl::EuclideanClusterExtraction<pcl::PointXYZ> ec;
	ec.setClusterTolerance (0.5); // 50cm
	ec.setMinClusterSize (10);
	ec.setMaxClusterSize (25000);
	ec.setSearchMethod (tree);
	ec.setInputCloud (cloud_filtered);
	ec.extract (cluster_indices);

	int j = 0;

	Eigen::Vector4f cloud_centroid;
	Eigen::Vector4f cloud_max;
	Eigen::Vector4f cloud_min;
	vision_msgs::Detection3DArray detection_arr;

	
	for (std::vector<pcl::PointIndices>::const_iterator it = cluster_indices.begin (); it != cluster_indices.end (); ++it)
	{
		pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_cluster (new pcl::PointCloud<pcl::PointXYZ>);

		for (const auto& idx : it->indices)
		  cloud_cluster->push_back ((*cloud_filtered)[idx]); //*
		cloud_cluster->width = cloud_cluster->size ();
		cloud_cluster->height = 1;
		cloud_cluster->is_dense = true;

		pcl::compute3DCentroid(*cloud_cluster,  cloud_centroid);
		pcl::getMinMax3D(*cloud_cluster, cloud_min,  cloud_max);

	
		vision_msgs::Detection3D msgOut;
		msgOut.header = msgIn.header;


		msgOut.bbox.size.x = cloud_max[0]-cloud_min[0];
		msgOut.bbox.size.y = cloud_max[1]-cloud_min[1];
		msgOut.bbox.size.z = cloud_max[2]-cloud_min[2];

		msgOut.bbox.center.position.x = cloud_centroid[0];
		msgOut.bbox.center.position.y = cloud_centroid[1];
		msgOut.bbox.center.position.z = cloud_centroid[2];
		

		msgOut.bbox.center.orientation.w = 1;

		detection_arr.detections.push_back(msgOut);

		j++;

	}



	pub_.publish (detection_arr) ;
}
}