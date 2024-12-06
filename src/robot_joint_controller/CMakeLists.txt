cmake_minimum_required(VERSION 3.5)
project(robot_joint_controller LANGUAGES CXX)

if(CMAKE_CXX_COMPILER_ID MATCHES "(GNU|Clang)")
  add_compile_options(-Wall -Wextra)
endif()

# set the same behavior for windows as it is on linux
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

# find dependencies
set(THIS_PACKAGE_INCLUDE_DEPENDS
  hardware_interface
  pluginlib
  rclcpp
  rclcpp_lifecycle
  controller_manager
  controller_interface
  realtime_tools
  robot_msgs
  urdf
)

# Specify the required version of ros2_control
find_package(controller_manager)
# Handle the case where the required version is not found
if(NOT controller_manager_FOUND)
  message(FATAL_ERROR "ros2_control version 4.0.0 or higher is required. "
  "Are you using the correct branch of the ros2_control_demos repository?")
endif()

# find dependencies
# find_package(backward_ros REQUIRED)
find_package(ament_cmake REQUIRED)
foreach(Dependency IN ITEMS ${THIS_PACKAGE_INCLUDE_DEPENDS})
  find_package(${Dependency} REQUIRED)
endforeach()

## COMPILE
add_library(
  robot_joint_controller
  SHARED
  src/robot_joint_controller.cpp
)
target_compile_features(robot_joint_controller PUBLIC cxx_std_17)
target_include_directories(robot_joint_controller PUBLIC
$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
$<INSTALL_INTERFACE:include/robot_joint_controller>
)

ament_target_dependencies(
  robot_joint_controller PUBLIC
  ${THIS_PACKAGE_INCLUDE_DEPENDS}
)

# target_link_libraries(robot_joint_controller ${urdf_LIBRARIES})

# Export hardware plugins
pluginlib_export_plugin_description_file(controller_interface robot_joint_controller_plugins.xml)

# INSTALL
# install(
#   DIRECTORY description/launch description/ros2_control description/urdf
#   DESTINATION share/ros2_control_demo_example_11
# )
# install(
#   DIRECTORY bringup/launch bringup/config
#   DESTINATION share/ros2_control_demo_example_11
# )
install(TARGETS robot_joint_controller
  EXPORT robot_joint_controller
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION bin
)

# if(BUILD_TESTING)
#   find_package(ament_cmake_pytest REQUIRED)

#   ament_add_pytest_test(example_11_urdf_xacro test/test_urdf_xacro.py)
#   ament_add_pytest_test(view_example_11_launch test/test_view_robot_launch.py)
#   ament_add_pytest_test(run_example_11_launch test/test_carlikebot_launch.py)
# endif()

## EXPORTS
ament_export_targets(robot_joint_controller HAS_LIBRARY_TARGET)
ament_export_dependencies(${THIS_PACKAGE_INCLUDE_DEPENDS})
ament_package()
