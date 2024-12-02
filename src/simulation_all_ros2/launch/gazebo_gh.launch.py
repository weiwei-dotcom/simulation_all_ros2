from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument, IncludeLaunchDescription
from launch.substitutions import LaunchConfiguration, Command, FindExecutable, PathJoinSubstitution, TextSubstitution
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch_ros.actions import Node
from launch_ros.substitutions import FindPackageShare
from ament_index_python.packages import get_package_share_directory
import os

def generate_launch_description():

    declared_areguments = []
    declared_areguments.append(DeclareLaunchArgument('world_file_name', default_value='TestSpace.world', description='World name'))
    declared_areguments.append(DeclareLaunchArgument('rname', default_value='gh1', description='Robot name'))

    robot_name = LaunchConfiguration("rname")
    declared_areguments.append(DeclareLaunchArgument('description_path', 
                                                     default_value=FindPackageShare(robot_name), 
                                                     description='description root path'))
    declared_areguments.append(DeclareLaunchArgument('dollar', default_value='$', description='dollar sign'))
    declared_areguments.append(DeclareLaunchArgument('paused', default_value='true', description='Pause simulation'))
    declared_areguments.append(DeclareLaunchArgument('use_sim_time', default_value='true', description='Use simulation time'))
    declared_areguments.append(DeclareLaunchArgument('gui', default_value='true', description='Enable GUI'))
    declared_areguments.append(DeclareLaunchArgument('headless', default_value='false', description='Headless mode'))
    declared_areguments.append(DeclareLaunchArgument('debug', default_value='false', description='Debug mode'))
    declared_areguments.append(DeclareLaunchArgument('user_debug', default_value='false', description='User debug mode'))

    world_file_name = LaunchConfiguration('world_file_name')

    # 这里要修改
    world_file_path = PathJoinSubstitution([FindPackageShare("simulation_all_ros2"), "worlds", world_file_name]) 
    gui_flag = LaunchConfiguration('gui')
    pause_flag = LaunchConfiguration('paused')
    headless_flag = LaunchConfiguration('headless')
    debug_flag = LaunchConfiguration('debug')
    description_path = LaunchConfiguration('description_path')
    # Include Gazebo empty world launch file
    gazebo_launch = IncludeLaunchDescription(
        PythonLaunchDescriptionSource([
            PathJoinSubstitution([FindPackageShare("gazebo_ros"), "launch", "gazebo.launch.py"])
        ]),
        launch_arguments={
            'world': world_file_path,
            'pause': pause_flag,
            'gui': gui_flag,
            'headless': headless_flag,
            'debug': debug_flag
        }.items()
    )

    xacro_path = PathJoinSubstitution([description_path, "xacro", "robot.xacro"])
    xacro_exe_path = FindExecutable(name="xacro")
    robot_urdf_content = Command([xacro_exe_path, " ", xacro_path, " use_sim:=true", " DEBUG:=", LaunchConfiguration('user_debug')])
    robot_description = {"robot_description": robot_urdf_content}
    # Load robot description
    robot_tf_node = Node(
        package='robot_state_publisher',
        executable='robot_state_publisher',
        output='screen',
        parameters=[robot_description]
    )
    
    # TODO:
    gazebo_name = robot_name

    # initial_joint_positions = ['-J', 'l_hip_roll'   , '0'   , '-J', 'r_hip_roll'   , '0'   , 
    #                            '-J', 'l_hip_yaw'    , '0'   , '-J', 'r_hip_yaw'    , '0'   ,
    #                            '-J', 'l_hip_pitch'  , '-0.2', '-J', 'r_hip_pitch'  , '-0.2', 
    #                            '-J', 'l_knee_pitch' , '0.4' , '-J', 'r_knee_pitch' , '0.4' ,
    #                            '-J', 'l_ankle_pitch', '-0.2', '-J', 'r_ankle_pitch', '-0.2']
    # Spawn robot in Gazebo
    robot_model = Node(
        package='gazebo_ros',
        executable='spawn_entity.py',
        name='urdf_spawner',
        output='screen',
        arguments=[
            '-entity', gazebo_name,
            '-z', '1.35',
            "-topic", "robot_description",
            '-robot_namespace', gazebo_name] 
            # + initial_joint_positions
    )

    # 加载 YAML 参数到 controller_manager
    control_yaml_path = PathJoinSubstitution([description_path, 'config', 'robot_control.yaml'])
    robot_config = Node(
        package='controller_manager',
        executable='ros2_control_node',
        # name='controller_manager',
        output='screen',
        parameters=[robot_description, control_yaml_path]
    )

    controller_names = ['joint_state_controller',
                        'l_hip_roll_controller', 'l_hip_yaw_controller', 'l_hip_pitch_controller',
                        'l_knee_pitch_controller', 'l_ankle_pitch_controller',
                        'r_hip_roll_controller', 'r_hip_yaw_controller', 'r_hip_pitch_controller',
                        'r_knee_pitch_controller', 'r_ankle_pitch_controller']

    # Load joint controller configurations from YAML
    joint_state_broadcaster_spawner = Node(
        package="controller_manager",
        executable="spawner.py",
        arguments=["joint_state_broadcaster", "--controller-manager", "/controller_manager"],
    )

    robot_controllers = []
    for controller_name in controller_names:
        robot_controllers.append(
            Node(
                package='controller_manager',
                executable='spawner.py',
                name='controller_spawner',
                output='screen',
                namespace = gazebo_name,
                arguments=[controller_name],
            )
        )

    nodes = [
        gazebo_launch,
        robot_model,
        robot_tf_node,
        robot_config,
        joint_state_broadcaster_spawner
    ]

            
    return LaunchDescription(declared_areguments + nodes + robot_controllers)