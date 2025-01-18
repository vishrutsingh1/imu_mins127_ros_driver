#include "imu_ros_driver/imu_sensor.h"



int main(int argc , char* argv[])
{
    rclcpp::init(argc,argv);
    IMU imu_obj;
    rclcpp::shutdown();
    return 0;
}