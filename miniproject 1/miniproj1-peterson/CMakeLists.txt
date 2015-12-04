cmake_minimum_required(VERSION 3.3)
project(miniproj1_peterson)
LINK_LIBRARIES(-lpthread)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp)
add_executable(miniproj1_peterson ${SOURCE_FILES})