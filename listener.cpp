#include "ros/ros.h"
#include "tugas1/custom.h"

void chatterCallback(const tugas1::custom::ConstPtr& msg){
    std::stringstream ss;
    ss <<msg->number1<<" "<<msg->nama<<" "<<msg->number2;
    ROS_INFO("[Listener] I heard: [%s]\n",(ss.str()).c_str());
}
int main (int argc,char **argv){
    ros::init(argc,argv,"listener_node");
    ros::NodeHandle node;
    ros::Subscriber sube = node.subscribe("chatter",1000,chatterCallback);
    ros::spin();
    return 0;
}