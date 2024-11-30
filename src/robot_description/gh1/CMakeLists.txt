cmake_minimum_required(VERSION 3.5)
project(gh1)

find_package(ament_cmake REQUIRED)
# find_package(rclcpp REQUIRED)
# find_package(std_msgs REQUIRED)
# find_package(tf2 REQUIRED)
# find_package(tf2_ros REQUIRED)
# find_package(ros2launch)

install(
  DIRECTORY config launch meshes urdf xacro
  DESTINATION share/${PROJECT_NAME}
)

ament_package()
