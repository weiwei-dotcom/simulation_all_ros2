source install/setup.bash

if [ "$1" == 'gh1' ] || [ "$1" == 'gh' ]; then
    ros2 launch simulation_all_ros2 gazebo_gh1.launch.py
elif [ "$1" == 'sz' ]; then
    ros2 launch simulation_all_ros2 gazebo_sz.launch.py
elif [ "$1" == 'mz' ]; then
    ros2 launch simulation_all_ros2 gazebo_mz.launch.py
elif [ "$1" == 'iris' ]; then
    ros2 launch simulation_all_ros2 gazebo_iris.launch.py
elif [ "$1" == 'qa01' ]; then
    ros2 launch simulation_all_ros2 gazebo_qa01.launch.py
else
    echo "please input the correct name of robot !"
fi