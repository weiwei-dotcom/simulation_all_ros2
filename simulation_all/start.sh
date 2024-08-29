#!/bin/bash

source devel/setup.bash

if [ $# == 1 ];then
    if [ "$1" == 'arm' ]; then
        roslaunch simulation_all gazebo_arm.launch
    elif [ "$1" == 'qr' ]; then
        roslaunch simulation_all gazebo_qr.launch
    elif [ "$1" == 'gh' ]; then
        roslaunch simulation_all gazebo_gh.launch
fi
elif [ $# == 2 ]; then
    if [ "$1" == 'qr' ]; then
            roslaunch simulation_all gazebo_qr.launch rname:=$2
        elif [ "$1" == 'gh' ]; then
            roslaunch simulation_all gazebo_gh.launch rname:=$2
    fi
else
    echo "please input bootargs!!"
fi