#  ____________
# |CMAKE CONFIG|
#  ‾‾‾‾‾‾‾‾‾‾‾‾
cmake_minimum_required(VERSION 3.7)
project(Motherload CXX)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake")

#  ____________
# |DEPENDENCIES|
#  ‾‾‾‾‾‾‾‾‾‾‾‾
# OpenGL
find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIR})
# SDL2
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})