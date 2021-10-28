#include "opencv2/opencv.hpp"
#include "ros/ros.h"
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>

int main(int argc, char **argv)
{
    //init ros
    ros::init(argc, argv, "webcam");

    ros::NodeHandle n;

    cv::VideoCapture camera;

    if (!camera.open(0))
        return 0;

    image_transport::ImageTransport it(n);

    image_transport::Publisher pub = it.advertise("camara/videofeed", 1);

    ros::Rate loop(30);

    while (ros::ok())
    {
        cv::Mat frame;
        camera >> frame;

        cv::namedWindow("webcam", cv::WINDOW_AUTOSIZE); // Create a window.
        cv::imshow("webcam",frame);          // Show our image inside it.

        sensor_msgs::ImagePtr msg = cv_bridge::CvImage(std_msgs::Header(), sensor_msgs::image_encodings::BGR8, frame).toImageMsg();

        pub.publish(msg);
        ROS_INFO("sendt");

        ros::spinOnce();

        loop.sleep();
    }
}
