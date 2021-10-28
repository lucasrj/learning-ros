#include "opencv2/opencv.hpp"
#include "ros/ros.h"
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>

int main(int argc, char **argv)
{
    //init ros
    ros::init(argc, argv, "static_image");

    ros::NodeHandle n;

    image_transport::ImageTransport it(n);

    image_transport::Publisher pub = it.advertise("camara/videofeed", 1);

    ros::Rate loop(1);

    while (ros::ok())
    {
        cv::Mat frame = cv::imread("/home/lucasrj/ros/test/src/webCamTest/images/NoeticNinjemys.png");

        cv::namedWindow("webcam", cv::WINDOW_AUTOSIZE); // Create a window.
        cv::imshow("webcam",frame);          // Show our image inside it.

        sensor_msgs::ImagePtr msg = cv_bridge::CvImage(std_msgs::Header(), sensor_msgs::image_encodings::BGR8, frame).toImageMsg();

        pub.publish(msg);

        ros::spinOnce();

        loop.sleep();
    }
}
