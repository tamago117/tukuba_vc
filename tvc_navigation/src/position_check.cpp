#include <ros/ros.h>
#include <iostream>
#include <string>
#include <geometry_msgs/Pose.h>
#include "tvc_navigation/tf_position.h"

int main(int argc, char** argv)
{
    ros::init(argc, argv, "position_check");
    ros::NodeHandle nh;
    ros::NodeHandle pnh("~");

    std::string odom_id, base_link_id;
    pnh.param<std::string>("odom_frame_id",odom_id,"odom");
    pnh.param<std::string>("base_link_frame_id",base_link_id,"base_link");
    int rate;
    pnh.param<int>("loop_rate", rate, 50);

    tf_position nowPosition(odom_id, base_link_id, rate);

    ros::Rate loop_rate(rate);

    geometry_msgs::Pose nowPose;
    while (ros::ok())
    {
            nowPose = nowPosition.getPose();
            std::cout << "position" << std::endl;
            std::cout << "         x : " << nowPose.position.x << " ";
            std::cout << "y : " << nowPose.position.y << " ";
            std::cout << "z : " << nowPose.position.z << std::endl;
            std::cout << "orientation" << std::endl;
            std::cout << "         x : " << nowPose.orientation.x << " ";
            std::cout << "y : " << nowPose.orientation.y << " ";
            std::cout << "z : " << nowPose.orientation.z << " ";
            std::cout << "w : " << nowPose.orientation.w << std::endl;
            std::cout<<std::endl;

        ros::spinOnce();
        loop_rate.sleep();
    }
    return 0;
}
