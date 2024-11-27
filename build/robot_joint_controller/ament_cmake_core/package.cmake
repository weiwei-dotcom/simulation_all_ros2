set(_AMENT_PACKAGE_NAME "robot_joint_controller")
set(robot_joint_controller_VERSION "0.0.0")
set(robot_joint_controller_MAINTAINER "Dr.-Ing. Denis Štogl <denis.stogl@stoglrobotics.de>, Bence Magyar <bence.magyar.robotics@gmail.com>, Christoph Froehlich <christoph.froehlich@ait.ac.at>")
set(robot_joint_controller_BUILD_DEPENDS "backward_ros" "hardware_interface" "pluginlib" "realtime_tools" "robot_msgs" "rclcpp" "rclcpp_lifecycle")
set(robot_joint_controller_BUILDTOOL_DEPENDS "ament_cmake")
set(robot_joint_controller_BUILD_EXPORT_DEPENDS "backward_ros" "hardware_interface" "pluginlib" "realtime_tools" "robot_msgs" "rclcpp" "rclcpp_lifecycle")
set(robot_joint_controller_BUILDTOOL_EXPORT_DEPENDS )
set(robot_joint_controller_EXEC_DEPENDS "bicycle_steering_controller" "controller_manager" "joint_state_broadcaster" "joint_state_publisher_gui" "robot_state_publisher" "ros2_control_demo_description" "ros2controlcli" "ros2launch" "rviz2" "xacro" "backward_ros" "hardware_interface" "pluginlib" "realtime_tools" "robot_msgs" "rclcpp" "rclcpp_lifecycle")
set(robot_joint_controller_TEST_DEPENDS )
set(robot_joint_controller_GROUP_DEPENDS )
set(robot_joint_controller_MEMBER_OF_GROUPS )
set(robot_joint_controller_DEPRECATED "")
set(robot_joint_controller_EXPORT_TAGS)
list(APPEND robot_joint_controller_EXPORT_TAGS "<build_type>ament_cmake</build_type>")