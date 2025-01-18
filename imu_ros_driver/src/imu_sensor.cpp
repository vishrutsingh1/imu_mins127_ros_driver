#include "imu_ros_driver/imu_sensor.h"


IMU::IMU():Node("imu_sensor_node")
{
    initialize();
    
    std::string device_id;
    this->declare_parameter<std::string>("device_id",device_id);
    this->get_parameter("device_id",device_id);
    
    _serial_port.set_paramater(device_id);
    int check = _serial_port.serial_initialize();
    if(!check)
    {
        RCLCPP_WARN(this->get_logger()," please check port and re-initialize!! ");
        return;
    }
    execute();
}

void IMU::initialize()
{
    _yaw_pub = this->create_publisher<std_msgs::msg::Float32>("yaw_angle",2);
    _pitch_pub = this->create_publisher<std_msgs::msg::Float32>("pitch_angle",2);
    _roll_pub = this->create_publisher<std_msgs::msg::Float32>("roll_angle",2);
}

void IMU::execute()
{
    auto yaw_message = std::make_shared<std_msgs::msg::Float32>();
    auto roll_message = std::make_shared<std_msgs::msg::Float32>();
    auto pitch_message = std::make_shared<std_msgs::msg::Float32>();
    
    rclcpp::WallRate loop_rate(20);
    while(rclcpp::ok())
    {
        _serial_port.send(_command);
        std::this_thread::sleep_for(std::chrono::milliseconds(30));
        
        std::vector<unsigned char> data;
        int check = _serial_port.receive(data,10);
        
        unsigned int roll_val =  static_cast<unsigned int>(data[3]) << 8 | static_cast<unsigned int>(data[4]);
        unsigned int pitch_val =  static_cast<unsigned int>(data[5]) << 8 | static_cast<unsigned int>(data[6]);
        unsigned int yaw_val =  static_cast<unsigned int>(data[7]) << 8 | static_cast<unsigned int>(data[8]);
        double roll_angle = (roll_val - 20000.0)/100.0;
        roll_message->data = roll_angle;
        double pitch_angle = (pitch_val - 20000.0)/100.0;
        pitch_message->data = pitch_angle;
        double yaw_angle = (yaw_val - 20000.0)/100.0;
        yaw_message->data = yaw_angle;
        _roll_pub->publish(*roll_message);
        _pitch_pub->publish(*pitch_message);
        _yaw_pub->publish(*yaw_message);
        loop_rate.sleep();
        _serial_port.flush();
    }
}