# Sets the minimum version of CMake required to build the native library.
cmake_minimum_required(VERSION 3.4.1)

# Declares and names the project.
project("bitmap")

# Project Folders
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")


# OPENCV Configuration
set(OpenCV_DIR ${CMAKE_CURRENT_SOURCE_DIR}/third-party/OpenCV/lib/cmake/opencv4/)

find_package(OpenCV REQUIRED COMPONENTS core imgproc highgui dnn)

# Executable
add_executable(
        bitmap

        ${CMAKE_CURRENT_SOURCE_DIR}/src/bitmap.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
)

# Target libraries
target_link_libraries(
        bitmap
        
        ${OpenCV_LIBS}
)

