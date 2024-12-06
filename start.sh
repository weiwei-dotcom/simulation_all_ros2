#!/bin/bash

source install/setup.bash

if [ $# == 1 ];then
    if [ "$1" == 'arm' ]; then
        ros2 launch simulation_all_ros2 gazebo_arm.launch.py
    elif [ "$1" == 'qr' ]; then
        ros2 launch simulation_all_ros2 gazebo_qr.launch.py
    elif [ "$1" == 'human' ]; then
        ros2 launch simulation_all_ros2 gazebo_gh.launch.py
    fi
elif [ $# == 2 ]; then
    if [ "$1" == 'qr' ]; then
        ros2 launch simulation_all_ros2 gazebo_qr.launch.py rname:=$2
    elif [ "$1" == 'human' ]; then
        ros2 launch simulation_all_ros2 gazebo_gh.launch.py rname:=$2
    elif [ "$1" == 'arm' ]; then
        ros2 launch simulation_all_ros2 gazebo_arm.launch.py rname:=$2
    fi
elif [ $# == 3 ]; then
    if [ "$1" == 'qr' ]; then
        if [ "$3" == 'user' ]; then
            ros2 launch simulation_all_ros2 gazebo_qr.launch.py rname:=$2
        elif [ "$3" == 'debug' ]; then
            ros2 launch simulation_all_ros2 gazebo_qr.launch.py rname:=$2 user_debug:=true
        fi
    elif [ "$1" == 'human' ]; then
        if [ "$3" == 'user' ]; then
            ros2 launch simulation_all_ros2 gazebo_gh.launch.py rname:=$2
        elif [ "$3" == 'debug' ]; then
            ros2 launch simulation_all_ros2 gazebo_gh.launch.py rname:=$2 user_debug:=true
        fi
    fi
else
    echo "please input bootargs!!"
fi