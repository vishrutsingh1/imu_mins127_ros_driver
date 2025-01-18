#include "imu_ros_driver/imu_sensor.h"



int main(int argc , char** argv)
{
    ros::init(argc,argv,"imu_sensor_node");
    IMU imu_obj;
    return 0;
}