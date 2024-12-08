from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument, IncludeLaunchDescription, RegisterEventHandler
from launch.event_handlers import OnProcessExit
from launch.substitutions import LaunchConfiguration, Command, FindExecutable, PathJoinSubstitution
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch_ros.actions import Node
from launch_ros.substitutions import FindPackageShare

def generate_launch_description():

    declared_areguments = []
    declared_areguments.append(DeclareLaunchArgument('description_path', 
                                                     default_value=FindPackageShare('mz'), 
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
    user_debug = LaunchConfiguration('user_debug')
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
            'use_sim_time': use_sim_time,
            'headless': headless_flag,
            'debug': debug_flag
        }.items()
    )


    # 加载 YAML 参数到 controller_manager
    xacro_path = PathJoinSubstitution([description_path, "xacro", "robot_system.xacro"])
    xacro_exe_path = FindExecutable(name="xacro")
    robot_urdf_content = Command([xacro_exe_path, " ", xacro_path, " ", "debug:=", user_debug])
    robot_description = {"robot_description": robot_urdf_content}
    control_yaml_path = PathJoinSubstitution([description_path, 'config', 'robot_control.yaml'])

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
            '-entity', "mz",
            '-z', '0.5',
            "-topic", "robot_description",
            '-robot_namespace', ""]  # 这里暂时不能有命名空间，
                                     # 不然gazebo_ros2_control会找不到robot_state_publisher服务名
                                     # 暂时不知道是不是因为找不到包含整个urdf内容的robot_description话题
                                     # 还是只是后面的gazebo_ros2_control找不到对应名称的robot_state_publisher服务
    )

    # Load joint controller configurations from YAML
    joint_state_broadcaster_spawner = Node(
        package="controller_manager",
        executable="spawner.py",
        arguments=["joint_state_broadcaster"],
    )

    joint_controller_names = ['FL_hip_controller',
                              'FL_thigh_controller',
                              'FL_calf_controller',
                              'FR_hip_controller',
                              'FR_thigh_controller',
                              'FR_calf_controller',
                              'RL_hip_controller',
                              'RL_thigh_controller',
                              'RL_calf_controller',
                              'RR_hip_controller',
                              'RR_thigh_controller',
                              'RR_calf_controller']
    controller_nodes = []
    for joint_controller_name in joint_controller_names:
        controller_nodes.append(
            Node(
                package='controller_manager',
                executable='spawner.py',
                output='screen',
                arguments=[joint_controller_name]
            )
        )

    nodes = [
        RegisterEventHandler(
            event_handler=OnProcessExit(
                target_action=robot_model,
                on_exit=[joint_state_broadcaster_spawner],
            )
        ),
        RegisterEventHandler(
            event_handler=OnProcessExit(
                target_action=joint_state_broadcaster_spawner,
                on_exit=controller_nodes,
            )
        ),
        robot_tf_node,
        gazebo_launch,
        robot_model,
    ]

            
    return LaunchDescription(declared_areguments + nodes)
