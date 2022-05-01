This is the readme of the final assignment of Robot Software Practicals by Job Mulder and Sam Bekkers



## To launch the programs:

**launch person detection package:**

```roslaunch opencv_person_detector detector.launch```

**launch obstacle detection package:**

```roslaunch pcl_obstacle_detector detector.launch```

**launch all the programs together**

```roslaunch control_barrel_world solution.launch```


### Explaintion of the code

**pcl obstacle detector**
made by Sam Bekkers

In ```pcl_obstacle_detector.h``` the class is made

In ```pcl_obstacle_detector_node.cpp``` the node in initialized

In ```pcl_obstacle_detector.cpp``` the functions are written


First, a filtering object is made for the back ground. The points are then clusterd. the center of the custer is detement and the size using the max an min values. That information is put in a array and published


**open CV person detector**
made by Job Mulder

In ```opencv_person_detector.h``` the class is made

In ```opencv_person_detector_node.cpp`` the node in initialized

In ```opencv_person_detector.cpp``` the functions are written

First, the data from the camera is collected. If a person is recognized, a square is drawn around a person and this info is published to two topics. This will result in a green box being drawn around the persons in the simulator.

**control barrel world**
made by Job Mulder and Sam Bekkers

In ```control_barrel_world.h``` the class is made

In ```control_barrel_world_node.cpp``` the node in initilized

In ```control_barrel_world.cpp``` the functions are written

The detections are put in a for loop to find the closest obstacle. When that obstacle is further than 4 meters apart the vehicle starts driving. When the obstacle is within 4 meters distance the car wil steer to the right or the left depending on the y value.

The person detection void takes the input from the person detector. When the amount of pixels is larger than 25000 the vehicle starts braking and shuts down the nodes so it will not drive again.

To compile the code and then run our solution, the following steps should be taken:
* ```source /opt/ros/melodic/setup.sh```
* ```cd ```
* ```mkdir -p catkin_ws/src```
* ```cd catkin_ws/src ```
* ```catkin_init_workspace```
* ```git clone 'this repository'
* ```git clone git@gitlab.ro47003.3me.tudelft.nl:students-2122/ro47003_simulator.git```
* ```cd ..```
* ```catkin_make```
* ```source devel/setup.sh```
* ```roslaunch control_barrel_world solution.launch```
