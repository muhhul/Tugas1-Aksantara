#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include "turtlesim/Pose.h"
#include <sstream>

using namespace std;

ros::Publisher velocity_publisher;
ros::Subscriber pose_subscriber;
turtlesim::Pose turtlesim_pose;

const double x_min = 0.0;
const double y_min = 0.0;
const double x_max = 10.0;
const double y_max = 10.0;
const double pi = 3.14159265359;

void chatterCallback(){
    ROS_INFO("Turtlesim moves");
}

void move(double speed,double distance, bool arah, bool cordinate){
    geometry_msgs::Twist velocity_message;
    if (arah==true and cordinate==true){
        velocity_message.linear.x=abs(speed);
    }else if (arah==false and cordinate==true){
        velocity_message.linear.x=-abs(speed);
    }else if (arah==true and cordinate==false){
        velocity_message.linear.y=abs(speed);
    }else{
        velocity_message.linear.y=-abs(speed);
    }
    double t0 = ros::Time::now().toSec();
    double distance_moved = 0.0;
    ros::Rate loop_rate(100);
    do{
        velocity_publisher.publish(velocity_message);
        double t1 = ros::Time::now().toSec();
        distance_moved = abs(speed * (t1-t0));
        ros::spinOnce();
        loop_rate.sleep();
    }while(distance_moved<distance);
    velocity_message.linear.x=0;
    velocity_publisher.publish(velocity_message);
}

int main(int argc, char **argv){
    ros::init(argc, argv, "turtlesim_node");
    ros::NodeHandle n;
    double speed, angular_speed;
    double distance, angle;

    velocity_publisher = n.advertise<geometry_msgs::Twist>("/turtle1/cmd_vel",10);
    //pose_subscriber = n.subscribe("/turtle1/pose",10,chatterCallback);

    ROS_INFO("START");
    ros::Rate loop_rate(0.5);
    while(true){
        move(3,11,true,true);
        move(3,11,true,false);
        move(3,11,false,true);
        move(3,11,false,false);
    }
    ros::spin();
    return 0;
}
    