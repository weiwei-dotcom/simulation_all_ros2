from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument, IncludeLaunchDescription
from launch.substitutions import LaunchConfiguration, Command, FindExecutable, PathJoinSubstitution
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch_ros.actions import Node
from launch_ros.substitutions import FindPackageShare

def generate_launch_description():

    declared_areguments = []
    declared_areguments.append(DeclareLaunchArgument('description_path', 
                                                     default_value=FindPackageShare('gh1'), 
                                                     description='description root path'))
    declared_areguments.append(DeclareLaunchArgument('dollar', default_value='$', description='dollar sign'))
    declared_areguments.append(DeclareLaunchArgument('paused', default_value='true', description='Pause simulation'))
    declared_areguments.append(DeclareLaunchArgument('use_sim_time', default_value='true', description='Use simulation time'))
    declared_areguments.append(DeclareLaunchArgument('gui', default_value='true', description='Enable GUI'))
    declared_areguments.append(DeclareLaunchArgument('headless', default_value='false', description='Headless mode'))
    declared_areguments.append(DeclareLaunchArgument('debug', default_value='false', description='Debug mode'))
    declared_areguments.append(DeclareLaunchArgument('user_debug', default_value='false', description='User debug mode'))

    # 这里要修改
    world_file_path = PathJoinSubstitution([FindPackageShare("simulation_all_ros2"), "worlds", "TestSpace.world"]) 
    gui = LaunchConfiguration('gui')
    pause_flag = LaunchConfiguration('paused')
    headless_flag = LaunchConfiguration('headless')
    debug_flag = LaunchConfiguration('debug')
    use_sim_time = LaunchConfiguration('use_sim_time')
    description_path = LaunchConfiguration('description_path')
    # Include Gazebo empty world launch file
    gazebo_launch = IncludeLaunchDescription(
        PythonLaunchDescriptionSource([
            PathJoinSubstitution([FindPackageShare("gazebo_ros"), "launch", "gazebo.launch.py"])
        ]),
        launch_arguments={
            'world': world_file_path,
            'pause': pause_flag,
            'gui': gui,
            'headless': headless_flag,
            'debug': debug_flag
        }.items()
    )


    # 加载 YAML 参数到 controller_manager
    xacro_path = PathJoinSubstitution([description_path, "xacro", "robot.xacro"])
    xacro_exe_path = FindExecutable(name="xacro")
    robot_urdf_content = Command([xacro_exe_path, " ", xacro_path, " use_sim:=true", " DEBUG:=", LaunchConfiguration('user_debug')])
    robot_description = {"robot_description": robot_urdf_content}
    control_yaml_path = PathJoinSubstitution([description_path, 'config', 'robot_control.yaml'])

    robot_config = Node(
        package='controller_manager',
        executable='ros2_control_node',
        output='screen',
        parameters=[robot_description, control_yaml_path]
    )

    # Load robot description
    robot_tf_node = Node(
        package='robot_state_publisher',
        executable='robot_state_publisher',
        output='screen',
        parameters=[robot_description]
    )

    # Spawn robot in Gazebo
    robot_model = Node(
        package='gazebo_ros',
        executable='spawn_entity.py',
        output='screen',
        arguments=[
            '-entity', "gh1",
            '-z', '1.35',
            "-topic", "robot_description",
            '-robot_namespace', "gh1_gazebo"] 
    )

    controller_names = ['l_hip_roll_controller']

    # Load joint controller configurations from YAML
    joint_state_broadcaster_spawner = Node(
        package="controller_manager",
        executable="spawner.py",
        arguments=["joint_state_broadcaster"],
    )

    robot_controllers = []
    for controller_name in controller_names:
        robot_controllers.append(
            Node(
                package='controller_manager',
                executable='spawner.py',
                output='screen',
                parameters=[robot_description],
                namespace = 'gh1', # 这里要修改为机器人的命名空间
                arguments=[controller_name]
            )
        )

    nodes = [
        gazebo_launch,
        robot_tf_node,
        robot_model,
        robot_config,
        joint_state_broadcaster_spawner
    ]

            
    return LaunchDescription(declared_areguments + nodes + robot_controllers)
    # return LaunchDescription(declared_areguments + nodes)
