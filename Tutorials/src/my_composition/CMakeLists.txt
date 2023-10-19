cmake_minimum_required(VERSION 3.8)
project(my_composition)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(std_srvs REQUIRED)
find_package(rclcpp_components REQUIRED)

include_directories(include)

# Create ament index resource which references the libraries in the binary dir
set(node_plugins "")

add_library(my_node_like_listener_component SHARED
  src/my_node_like_listener_component)

target_compile_definitions(my_node_like_listener_component
  PRIVATE "COMPOSITION_BUILDING_DLL")

ament_target_dependencies(my_node_like_listener_component
  "rclcpp"
  "rclcpp_components"
  "std_msgs")

rclcpp_components_register_nodes(my_node_like_listener_component "my_composition::MyNodeLikeListener")

set(node_plugins "${node_plugins}my_composition::MyNodeLikeListener;$<TARGET_FILE:my_node_like_listener_component>\n")

add_library(my_listener_component SHARED
  src/my_listener_component)
target_compile_definitions(my_listener_component
  PRIVATE "COMPOSITION_BUILDING_DLL")
ament_target_dependencies(my_listener_component
  "rclcpp"
  "rclcpp_components"
  "std_msgs")
rclcpp_components_register_nodes(my_listener_component "my_composition::MyListener")
set(node_plugins "${node_plugins}my_composition::MyListener;$<TARGET_FILE:my_listener_component>\n")


install(TARGETS
  my_node_like_listener_component
  my_listener_component
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION bin)

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

ament_package()
