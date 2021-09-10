#include <ros/ros.h>
#include <tf/transform_broadcaster.h>
#include <geometry_msgs/PoseStamped.h>
#include <std_msgs/Int32MultiArray.h>
#include <nav_msgs/Odometry.h>
#include <string>
#include <math.h>
#include <vector>

void odom_callback(const nav_msgs::Odometry& odom_message)
{
    static tf::TransformBroadcaster br;
    tf::Transform transform;

    transform.setOrigin(tf::Vector3(odom_message.pose.pose.position.x, odom_message.pose.pose.position.y, odom_message.pose.pose.position.z));
    tf::Quaternion q;
    //q.setRPY(0, 0, float_sensor_data[14]);
    q.setX(odom_message.pose.pose.orientation.x);
    q.setY(odom_message.pose.pose.orientation.y);
    q.setZ(odom_message.pose.pose.orientation.z);
    q.setW(odom_message.pose.pose.orientation.w);
    transform.setRotation(q);
    br.sendTransform(tf::StampedTransform(transform, ros::Time::now(), odom_message.header.frame_id, odom_message.child_frame_id));
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "odom_tf_broadcaster");
    ros::NodeHandle nh;

    ros::Subscriber odom_sub = nh.subscribe("odom", 10, odom_callback);

    ros::spin();

    return 0;
}