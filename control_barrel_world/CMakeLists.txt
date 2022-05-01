# What version of CMake is needed?
cmake_minimum_required (VERSION 2.8.3)
#Nameofthispackage.
project(control_barrel_world)
# Find the catkin build system , and any other packages on
# which we depend .
find_package(catkin REQUIRED COMPONENTS roscpp geometry_msgs turtlesim prius_msgs pcl_ros cv_bridge vision_msgs)
find_package (OpenCV REQUIRED)
# Declare our catkin package
catkin_package()
# Specify locations of header files .
include_directories (include ${catkin_INCLUDE_DIRS}  ${OpenCV_INCLUDE_DIRS})
# Declare the executable , along with its source files . If
# there are multiple executables , use multiple copies of
#thisline.

add_executable (control_barrel_world_node src/control_barrel_world_node.cpp src/control_barrel_world.cpp)

# Specify libraries against which to link . Again , this
# line should be copied for each distinct executable in
#thepackage.

target_link_libraries (control_barrel_world_node ${catkin_LIBRARIES} ${OpenCV_LIBRARIES})
