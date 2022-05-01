#include"control_barrel_world.h"

namespace carControl{




car_control::car_control() {

// Create a publisher object.
pub_ = nh_.advertise<prius_msgs::Control>( "/prius", 1);


// Create a subscriber object .
sub1_ = nh_.subscribe("/opencv_person_detector_node/detections", 1, &car_control::person_detection, this);
sub2_ = nh_.subscribe("/pcl_obstacle_detector_node/detections", 1, &car_control::obstacle_detection, this);
ROS_INFO_STREAM("hello this is selfdriving prius");
}

void car_control::obstacle_detection(const vision_msgs::Detection3DArray& msgLidar){
prius_msgs::Control msgOut; //message output

ROS_INFO_STREAM("Detection of pion is recieved");

// init variables
  

  double distance = 4;
  double x_edge;
  double y_edge;
  double x_center;
  double y_center;


  // loop for finding closest object
  if (shutdown_car == false){


    msgOut.throttle = 1;
    for (int i = 0; i < 10; i++){
      if (msgLidar.detections[i].bbox.center.position.x > 0.2){
        if (sqrt(msgLidar.detections[i].bbox.center.position.x * msgLidar.detections[i].bbox.center.position.x 
          + msgLidar.detections[i].bbox.center.position.y * msgLidar.detections[i].bbox.center.position.x) < distance){
          
          x_center = msgLidar.detections[i].bbox.center.position.x;
          y_center = msgLidar.detections[i].bbox.center.position.y;
          x_edge = x_center - msgLidar.detections[i].bbox.size.x;
          y_edge = y_center - msgLidar.detections[i].bbox.size.y;

          distance = sqrt(x_edge*x_edge + y_edge*y_edge);
        }
      }
    }

    if (distance > 4){
      msgOut.throttle = 1;
      msgOut.steer = 0;
    }

    if (distance < 4){

        if (y_edge > 0){
          msgOut.steer = -1;
          msgOut.throttle = 1;

        }

        if (y_edge < 0){
          msgOut.steer = 1;
          msgOut.throttle = 1;
        }
      
      }
       pub_.publish(msgOut);
       ROS_INFO_STREAM("output throttle ="<<msgOut.throttle<<" output steer ="<<msgOut.steer << "output brake =" <<msgOut.brake);


    }

    if(shutdown_car == true){ 
      msgOut.brake = 1;
      msgOut.shift_gears = 1;
      msgOut.throttle = 0;
      pub_.publish(msgOut);
      ROS_INFO_STREAM("brake loop");

    }
  }




void car_control::person_detection(const vision_msgs::Detection2DArray& msgDetect){

  prius_msgs::Control msgOut;

  for (const vision_msgs::Detection2D & current_image : msgDetect.detections){

    if (current_image.bbox.size_x*current_image.bbox.size_y > 25000){
      shutdown_car = true;
      msgOut.shift_gears = 1;
      msgOut.throttle = 0;
      msgOut.brake = 1;
      pub_.publish(msgOut);

      
      ROS_WARN_STREAM("person in front of vehicle, auto brake");
      ROS_INFO_STREAM("output throttle ="<<msgOut.throttle<<" output steer ="<<msgOut.steer << "output brake =" <<msgOut.brake);

      
      
      }

    }

  }
}



