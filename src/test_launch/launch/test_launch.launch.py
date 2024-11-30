from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument, IncludeLaunchDescription
from launch.substitutions import LaunchConfiguration, Command, FindExecutable, PathJoinSubstitution, EnvironmentVariable
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch_ros.actions import Node
from launch_ros.substitutions import FindPackageShare
import os

print("1")
test_string_path = os.path.join("home","wl", "Desktop", "token.txt")
print(test_string_path)


def generate_launch_description():
    robot_model = Node(
        package='gazebo_ros',
        executable='spawn_entity.py',
        name='urdf_spawner',
        output='screen',
        arguments=[
            '-entity', ,
            '-z', '1.35',
            '-file', robot_description_content,
            '-robot_namespace', gazebo_name, 
            initial_joint_positions 
        ]
    )
    return LaunchDescription([robot_model])
