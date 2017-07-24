cmake_minimum_required(VERSION 3.5)
project(ros2_daemon_client_cpp)

# Add support for C++11
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

find_package(ament_cmake REQUIRED)
find_package(xmlrpcpp)
find_package(rclcpp)

# List of all necessary header directories
set(INCLUDE_DIRS
  include
  ${xmlrpcpp_INCLUDE_DIRS}
  ${rclcpp_INCLUDE_DIRS}
)
include_directories(${INCLUDE_DIRS})

set(LIBS
  ${xmlrpcpp_LIBRARIES}
  ${rclcpp_LIBRARIES}
)

#### Add a library
add_library(${PROJECT_NAME} SHARED
  src/Ros2DaemonClient.cpp
)
target_link_libraries(${PROJECT_NAME} ${LIBS})
set(LIBS ${LIBS} ${PROJECT_NAME})


############################################################
# Define installation rules
#

install(
  TARGETS ${PROJECT_NAME}
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION bin
)

## Mark cpp header files for installation
install(
  DIRECTORY include/${PROJECT_NAME}/
  DESTINATION include/${PROJECT_NAME}
  FILES_MATCHING PATTERN "*.hpp"
  PATTERN ".svn" EXCLUDE
)

# Export include dependencies, directories, and libraries
ament_export_dependencies(ament_cmake)
ament_export_dependencies(xmlrpcpp)
ament_export_include_directories(${INCLUDE_DIRS})
ament_export_libraries(${PROJECT_NAME} ${LIBS})

# Must be at the bottom
ament_package()
