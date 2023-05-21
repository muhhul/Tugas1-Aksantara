#include "ros/ros.h"
#include "tugas1/custom.h"
#include <sstream>

int main(int argc,char **argv){
    ros::init(argc,argv,"talker_node");
    ros::NodeHandle n;
    ros::Publisher chatter_publisher = n.advertise<tugas1::custom>("chatter",1000);
    ros::Rate loop_rate(0.5);
    int count = 0;
    while(ros::ok()){
        tugas1::custom msg;
        std::stringstream ss;
        msg.number1 = count;
        msg.nama = "aksantara";
        msg.number2 = (float)count;
        ss <<msg.number1<<" "<<msg.nama<<" "<<msg.number2;
        ROS_INFO("[Talker] I published %s\n",(ss.str()).c_str());
        chatter_publisher.publish(msg);
        ros::spinOnce();
        loop_rate.sleep();
        count++;
    }
    return 0;
}