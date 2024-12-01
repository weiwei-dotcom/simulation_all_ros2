from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument
from launch.substitutions import LaunchConfiguration, Command, FindExecutable, PathJoinSubstitution
from launch_ros.actions import Node
from launch_ros.substitutions import FindPackageShare

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

    description_path = LaunchConfiguration('description_path')


    xacro_path = PathJoinSubstitution([description_path, "xacro", "robot.xacro"])
    xacro_exe_path = FindExecutable(name="xacro")
    robot_urdf_content = Command([xacro_exe_path, " ", xacro_path, " use_sim:=true", " DEBUG:=", LaunchConfiguration('user_debug')])
    robot_description = {"robot_description": robot_urdf_content}
    
    gazebo_name = robot_name

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
 
    return LaunchDescription(declared_areguments+[robot_config] + robot_controllers)