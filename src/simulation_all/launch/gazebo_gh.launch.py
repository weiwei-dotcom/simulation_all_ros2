from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument, IncludeLaunchDescription
from launch.substitutions import LaunchConfiguration, Command
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch_ros.actions import Node
import os


def generate_launch_description():
    # Declare launch arguments
    return LaunchDescription([
        DeclareLaunchArgument('wname', default_value='TestSpace', description='World name'),
        DeclareLaunchArgument('rname', default_value='gr1t1', description='Robot name'),
        DeclareLaunchArgument('paused', default_value='true', description='Pause simulation'),
        DeclareLaunchArgument('use_sim_time', default_value='true', description='Use simulation time'),
        DeclareLaunchArgument('gui', default_value='true', description='Enable GUI'),
        DeclareLaunchArgument('headless', default_value='false', description='Headless mode'),
        DeclareLaunchArgument('debug', default_value='false', description='Debug mode'),
        DeclareLaunchArgument('user_debug', default_value='false', description='User debug mode'),
        DeclareLaunchArgument('initial_joint_positions',
                              default_value='''-J l_hip_roll 0 -J l_hip_yaw 0 -J l_hip_pitch -0.2 
                              -J l_knee_pitch 0.4 -J l_ankle_pitch -0.2 
                              -J r_hip_roll 0 -J r_hip_yaw 0 -J r_hip_pitch -0.2 
                              -J r_knee_pitch 0.4 -J r_ankle_pitch -0.2''',
                              description='Initial joint configuration of the robot'),
        
        # Include Gazebo empty world launch file
        IncludeLaunchDescription(
            PythonLaunchDescriptionSource([
                os.path.join(
                    os.getenv('GAZEBO_ROS_PACKAGE_PATH', 'gazebo_ros'), 'launch', 'gazebo.launch.py'
                )
            ]),
            launch_arguments={
                'world': [os.getenv('SIMULATION_ALL_PATH', 'simulation_all'), '/worlds/', LaunchConfiguration('wname'), '.world'],
                'paused': LaunchConfiguration('paused'),
                'use_sim_time': LaunchConfiguration('use_sim_time'),
                'gui': LaunchConfiguration('gui'),
                'headless': LaunchConfiguration('headless'),
                'debug': LaunchConfiguration('debug'),
            }.items()
        ),
        
        # Load robot description
        Node(
            package='robot_state_publisher',
            executable='robot_state_publisher',
            output='screen',
            parameters=[{
                'robot_description': Command([
                    os.path.join(os.getenv('XACRO_PATH', 'xacro'), 'xacro'), ' --inorder ',
                    os.path.join(LaunchConfiguration('rname'), '_description/xacro/robot.xacro'),
                    ' DEBUG:=', LaunchConfiguration('user_debug')
                ])
            }]
        ),
        
        # Spawn robot in Gazebo
        Node(
            package='gazebo_ros',
            executable='spawn_entity.py',
            name='urdf_spawner',
            output='screen',
            arguments=[
                '-entity', [LaunchConfiguration('rname'), '_gazebo'],
                '-z', '1.35',
                '-param', 'robot_description',
                '-robot_namespace', LaunchConfiguration('rname'),
                LaunchConfiguration('initial_joint_positions')
            ]
        ),
        
        # Load joint controller configurations from YAML
        Node(
            package='controller_manager',
            executable='spawner.py',
            name='controller_spawner',
            output='screen',
            namespace=[LaunchConfiguration('rname'), '_gazebo'],
            arguments=[
                'joint_state_controller',
                'l_hip_roll_controller', 'l_hip_yaw_controller', 'l_hip_pitch_controller',
                'l_knee_pitch_controller', 'l_ankle_pitch_controller',
                'r_hip_roll_controller', 'r_hip_yaw_controller', 'r_hip_pitch_controller',
                'r_knee_pitch_controller', 'r_ankle_pitch_controller'
            ]
        ),
    ])