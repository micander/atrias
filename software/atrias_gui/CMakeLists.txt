# Devin Koepl

cmake_minimum_required(VERSION 2.4.6)
include($ENV{ROS_ROOT}/core/rosbuild/rosbuild.cmake)

# Set the build type.  Options are:
#  Coverage       : w/ debug symbols, w/o optimization, w/ code-coverage
#  Debug          : w/ debug symbols, w/o optimization
#  Release        : w/o debug symbols, w/ optimization
#  RelWithDebInfo : w/ debug symbols, w/ optimization
#  MinSizeRel     : w/o debug symbols, w/ optimization, stripped binaries
#set(ROS_BUILD_TYPE RelWithDebInfo)

rosbuild_init()

#set the default path for built executables to the "bin" directory
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
#set the default path for built libraries to the "lib" directory
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

#uncomment if you have defined messages
#rosbuild_genmsg()
#uncomment if you have defined services
rosbuild_gensrv()

rosbuild_add_boost_directories()

include_directories(../../robot_definitions)

#common commands for building c++ executables and libraries
#rosbuild_add_library(${PROJECT_NAME} src/example.cpp)
#target_link_libraries(${PROJECT_NAME} another_library)
#rosbuild_add_boost_directories()
#rosbuild_link_boost(${PROJECT_NAME} thread)
#rosbuild_add_executable(example examples/example.cpp)
#target_link_libraries(example ${PROJECT_NAME})

rosbuild_add_executable(atrias_gui src/atrias_gui.cpp)
rosbuild_add_executable(atrias_gui src/StatusGui.cpp)

#old method for including gtkmm
#include($ENV{ROS_ROOT}/core/rosbuild/FindPkgConfig.cmake)
#pkg_check_modules(GTKMM REQUIRED gtkmm-2.4)
#include_directories(${GTKMM_INCLUDE_DIRS})
#link_directories(${GTKMM_LIBRARY_DIRS})
#target_link_libraries(atrias_gui ${GTKMM_LIBRARIES})

find_package(GTK2 2.4 COMPONENTS gtk gtkmm)
if (GTK2_FOUND)
	include_directories(${GTK2_INCLUDE_DIRS})
	target_link_libraries(atrias_gui ${GTK2_LIBRARIES})
endif (GTK2_FOUND)

target_link_libraries(atrias_gui controller_metadata)
target_link_libraries(atrias_gui roslib)
