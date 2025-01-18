#ifndef _ROS_IMU_SENSOR_H_
#define _ROS_IMU_SENSOR_H_

#include <ros/ros.h>
#include <std_msgs/Float32.h>
#include <imu_ros_driver/serial.h>
#include <iostream>
#include <vector>
#include <thread>


class IMU 
{

    public:
        IMU();
        void initialize();
        void execute();
    
    private:
        ros::Publisher _roll_pub;
        ros::Publisher _pitch_pub;
        ros::Publisher _yaw_pub;
        std::vector<unsigned char> _command = {0x01,0x03,0x00,0x01,0x00,0x03,0x54,0x0B};
        PGV::Serial _serial_port;
        std::string _port_name;
        ros::NodeHandle _node;

};

#endif