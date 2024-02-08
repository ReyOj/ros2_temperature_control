import os
from ament_index_python.packages import get_package_share_path
from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument
from launch.substitutions import LaunchConfiguration
from launch_ros.actions import Node

def generate_launch_description():
    pkg_share = os.path.join(get_package_share_path('temperature'))
    config_path = os.path.join(pkg_share, 'config', 'param.yaml')

    config_arg = DeclareLaunchArgument(name='config', default_value=config_path, description='Path to config file')

    temp = Node(
        package='temperature',
        name='temp',
        executable='temp',
        parameters=[LaunchConfiguration('config')]
    )
    return LaunchDescription([
        config_arg,
        temp
    ])