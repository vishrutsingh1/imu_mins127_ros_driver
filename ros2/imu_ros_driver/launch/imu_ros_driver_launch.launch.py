from launch import LaunchDescription
from launch_ros.actions import Node


def generate_launch_description():
    return LaunchDescription([Node(

        package="imu_ros_driver",
        executable="imu_ros_driver_node",
        output="screen",
        emulate_tty=True,
        parameters = [{"device_id" : "/dev/ttyUSB0"}]

)])