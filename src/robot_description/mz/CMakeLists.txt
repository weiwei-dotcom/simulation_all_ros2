cmake_minimum_required(VERSION 3.5)
project(mz)

find_package(ament_cmake REQUIRED)


install(
  DIRECTORY config launch meshes urdf xacro
  DESTINATION share/${PROJECT_NAME}
)

ament_package()
