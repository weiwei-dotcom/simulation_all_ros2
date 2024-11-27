#----------------------------------------------------------------
# Generated CMake target import file.
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "robot_joint_controller::robot_joint_controller" for configuration ""
set_property(TARGET robot_joint_controller::robot_joint_controller APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
set_target_properties(robot_joint_controller::robot_joint_controller PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_NOCONFIG "CXX"
  IMPORTED_LOCATION_NOCONFIG "${_IMPORT_PREFIX}/lib/librobot_joint_controller.a"
  )

list(APPEND _IMPORT_CHECK_TARGETS robot_joint_controller::robot_joint_controller )
list(APPEND _IMPORT_CHECK_FILES_FOR_robot_joint_controller::robot_joint_controller "${_IMPORT_PREFIX}/lib/librobot_joint_controller.a" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
