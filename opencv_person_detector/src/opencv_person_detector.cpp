#include<ros/ros.h>
#include"opencv_person_detector.h"

namespace opencv_person_detector{




OpenCVPersonDetector::OpenCVPersonDetector(){
cv::namedWindow("view");

image_transport::ImageTransport it(nh_);

//create a subscriber object for the front_camera

sub_ = it.subscribe("prius/front_camera/image_raw", 1, &OpenCVPersonDetector::detectAndDraw, this);
visualPtr_ = it.advertise( "/opencv_person_detector_node/visual", 1, this);

//creating a publisher that publishes to the simulator

//detectPtr = new image_transport::Publisher(it.advertise("/opencv_person_detector_node/detections", 1));
detections_pub_ = nh_.advertise<vision_msgs::Detection2DArray>("/opencv_person_detector_node/detections", 1);

cv::destroyWindow("view");

}



void OpenCVPersonDetector::detectAndDraw(const sensor_msgs::ImageConstPtr& msg)
{
    cv_bridge::CvImageConstPtr cv_ptr;
    cv_ptr = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::BGR8);
    Mat mat_image = cv_ptr->image;
    imshow("people detector", mat_image);

    vision_msgs::Detection2DArray detections;

    HOGDescriptor hog;
    hog.setSVMDetector(HOGDescriptor::getDefaultPeopleDetector());
    cv::namedWindow("people detector", 1);

    vector<Rect> found, found_filtered;
    double t = (double) getTickCount();
    // Run the detector with default parameters. to get a higher hit-rate
    // (and more false alarms, respectively), decrease the hitThreshold and
    // groupThreshold (set groupThreshold to 0 to turn off the grouping completely).
    hog.detectMultiScale(mat_image, found, 0, Size(8,8), Size(32,32), 1.05, 2);
    t = (double) getTickCount() - t;
    cout << "detection time = " << (t*1000./cv::getTickFrequency()) << " ms" << endl;

    for(size_t i = 0; i < found.size(); i++ )
    {
        Rect r = found[i];

        size_t j;
        // Do not add small detections inside a bigger detection.
        for ( j = 0; j < found.size(); j++ )
            if ( j != i && (r & found[j]) == r )
                break;

        if ( j == found.size() )
            found_filtered.push_back(r);
    }

    for (size_t i = 0; i < found_filtered.size(); i++)
    {
        Rect r = found_filtered[i];

        // The HOG detector returns slightly larger rectangles than the real objects,
        // so we slightly shrink the rectangles to get a nicer output.
        r.x += cvRound(r.width*0.1);
        r.width = cvRound(r.width*0.8);
        r.y += cvRound(r.height*0.07);
        r.height = cvRound(r.height*0.8);
        rectangle(mat_image, r.tl(), r.br(), cv::Scalar(0,255,0), 3);

        vision_msgs::Detection2D detection;
        detection.bbox.center.x = r.x;
        detection.bbox.center.y = r.y;
        detection.bbox.size_x = r.width;
        detection.bbox.size_y = r.height;


        vision_msgs::ObjectHypothesisWithPose hypo;
        hypo.id = 0;
        hypo.score = 1;
        detection.results.push_back(hypo);
        detections.detections.push_back(detection);
    }

    std_msgs::Header header; // empty header
    cv_bridge::CvImage img_bridge;
    sensor_msgs::Image img_msg;
    img_bridge = cv_bridge::CvImage(header, sensor_msgs::image_encodings::BGR8, mat_image);
    img_bridge.toImageMsg(img_msg); // from cv_bridge to sensor_msgs::Image

    visualPtr_.publish(img_msg); // ros::Publisher pub_img = node.advertise<sensor_msgs::Image>("topic", queuesize);
    detections_pub_.publish(detections);
    //detectPtr->publish(detections); //publisher to the vision_msgs
}

}