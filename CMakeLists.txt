cmake_minimum_required(VERSION 3.8)
project(test)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(geometry_msgs REQUIRED)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights
  # comment the line when a copyright and license is added to all source files
  set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # comment the line when this package is in a git repo and when
  # a copyright and license is added to all source files
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

add_executable(talk src/pub.cpp)
ament_target_dependencies(talk rclcpp std_msgs)

add_executable(listener src/sub_int.cpp)
ament_target_dependencies(listener rclcpp std_msgs)

add_executable(intpub src/Pint.cpp)
ament_target_dependencies(intpub rclcpp std_msgs)

add_executable(intsub src/Sint.cpp)
ament_target_dependencies(intsub rclcpp std_msgs)

add_executable(forward src/turtlecmd.cpp)
ament_target_dependencies(forward rclcpp geometry_msgs)

install (TARGETS
  talk
  listener
  intpub
  intsub
  forward
  DESTINATION lib/${PROJECT_NAME}
)

ament_package()
