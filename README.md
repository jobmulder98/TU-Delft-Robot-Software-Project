# TU Delft - Robot Software Practicals Final Assignment
Course: Robot Software Practicals
Programming Language: C++
Grade: Pass (no grade)

## Project Description
In this assignment a fellow student and I have worked with a virtual controllable Prius vehicle, driving through a virtual environment. The vehicle must use its sensors to detect obstacles and pedestrians, and use these detections to generate control instructions. This way, the vehicle should drive automatically between a path
outlined by cones/barrels, without hitting any obstacle or pedestrian. The virtual vehicle has two main sensors: a front-facing camera behind the windscreen, and a 360 degree top-mounted lidar. The vehicle receives camera images and lidar pointclouds as ROS topics, and can also be controlled by publishing control messages to a specified topic. The goal of this final assignment was to lead the self driving car through the environment without hitting (dynamic) objects. 

![image](https://user-images.githubusercontent.com/101323001/166163325-1c66c676-6286-4d12-a0ec-3a521ea22cd4.png)

## Disclaimer
Since this project was made in a gitlab from TU Delft, the repository with the environment with the Prius is not available anymore. Therefore, running this code won't work. However, don't be shy to check out the code! 

## Launching the programs
**launch person detection package:**
```roslaunch opencv_person_detector detector.launch```

**launch obstacle detection package:**
```roslaunch pcl_obstacle_detector detector.launch```

**launch all the programs together**
```roslaunch control_barrel_world solution.launch```

## Explaintion of the code
**pcl obstacle detector**
Made by Sam Bekkers
In ```pcl_obstacle_detector.h``` the class is made
In ```pcl_obstacle_detector_node.cpp``` the node in initialized
In ```pcl_obstacle_detector.cpp``` the functions are written

First, a filtering object is made for the back ground. The points are then clusterd. the center of the custer is detement and the size using the max an min values. That information is put in a array and published

**open CV person detector**
Made by Job Mulder

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

