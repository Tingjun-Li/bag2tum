cmake_minimum_required(VERSION 3.0.2)
project(rosbag2tum)

find_package(catkin REQUIRED COMPONENTS
  cv_bridge
  roscpp
  sensor_msgs
  std_msgs
)

find_package(OpenCV 4 QUIET)
if(NOT OpenCV_FOUND)
   find_package(OpenCV 2.4.3 QUIET)
   if(NOT OpenCV_FOUND)
      message(FATAL_ERROR "OpenCV > 2.4.3 not found.")
   endif()
endif()

catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES rosbag2tum
  CATKIN_DEPENDS cv_bridge roscpp sensor_msgs std_msgs
#  DEPENDS system_lib
)

include_directories(
# include
  ${OpenCV_INCLUDE_DIRS}
  ${catkin_INCLUDE_DIRS}
)

# add_dependencies(${PROJECT_NAME} ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})

 add_executable(bag2tum src/bagToTUM.cpp)
 target_link_libraries(bag2tum ${catkin_LIBRARIES} ${OpenCV_LIBS})
