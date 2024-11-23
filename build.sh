#!/bin/bash
rm -r install/ build/

source /opt/ros/foxy/setup.bash

colcon build --packages-select simulation_all_ros2