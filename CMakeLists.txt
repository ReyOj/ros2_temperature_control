cmake_minimum_required(VERSION 3.8)
project(temperature)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)

add_executable(temp src/temp.cpp)
ament_target_dependencies(temp rclcpp std_msgs)

install(DIRECTORY
  config
  launch
  DESTINATION share/${PROJECT_NAME})

install(TARGETS
temp
DESTINATION lib/${PROJECT_NAME})

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()
