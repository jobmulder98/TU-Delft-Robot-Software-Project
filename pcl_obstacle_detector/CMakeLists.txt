# What version of CMake is needed? 
cmake_minimum_required (VERSION 2.8.3)
#Nameofthispackage. 
project(pcl_obstacle_detector)
# Find the catkin build system , and any other packages on 
# which we depend .
find_package(catkin REQUIRED COMPONENTS roscpp sensor_msgs pcl_ros )

# Declare our catkin package  
catkin_package()
# Specify locations of header files . 
include_directories (include ${catkin_INCLUDE_DIRS})
# Declare the executable , along with its source files . If 
# there are multiple executables , use multiple copies of 
#thisline.

add_executable(pcl_obstacle_detector_node src/pcl_obstacle_detector_node.cpp src/pcl_obstacle_detector.cpp)

# Specify libraries against which to link . Again , this 
# line should be copied for each distinct executable in 
#thepackage.

target_link_libraries (pcl_obstacle_detector_node ${catkin_LIBRARIES})