#ifndef _ROS_IMU_SENSOR_H_
#define _ROS_IMU_SENSOR_H_

#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/float32.hpp>
#include <imu_ros_driver/serial.h>
#include <iostream>
#include <vector>


class IMU : public rclcpp::Node
{

    public:
        IMU();
        void initialize();
        void execute();
    
    private:
        rclcpp::Publisher<std_msgs::msg::Float32>::SharedPtr _roll_pub;
        rclcpp::Publisher<std_msgs::msg::Float32>::SharedPtr _pitch_pub;
        rclcpp::Publisher<std_msgs::msg::Float32>::SharedPtr _yaw_pub;
        std::vector<unsigned char> _command = {0x01,0x03,0x00,0x01,0x00,0x03,0x54,0x0B};
        PGV::Serial _serial_port;
        std::string _port_name;

};

#endif