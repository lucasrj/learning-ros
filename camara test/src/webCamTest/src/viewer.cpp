#include "opencv2/opencv.hpp"
#include "ros/ros.h"
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>

void viewer(const sensor_msgs::ImageConstPtr msg){
    cv_bridge::CvImagePtr cv_image;
    cv_image = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::BGR8);

    cv::Mat image = cv_image->image;


    cv::imshow("Display window", image);       // Show our image inside it.

    cv::waitKey(30);
}




int main(int argc, char **argv)
{
    ros::init(argc, argv,"viewer");

    ros::NodeHandle n;

    image_transport::ImageTransport it(n);

    image_transport::Subscriber sub = it.subscribe("camara/videofeed",1,viewer);


    ros::spin();

    return 0;



}