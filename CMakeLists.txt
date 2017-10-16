#  ____________
# |CMAKE CONFIG|
#  ‾‾‾‾‾‾‾‾‾‾‾‾
cmake_minimum_required(VERSION 3.7)
project(Motherload CXX)

set(CMAKE_BUILD_TYPE debug)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake")
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)
set(PROJECT_SOURCE_DIR ${CMAKE_BINARY_DIR}/src)

include_directories("${PROJECT_SOURCE_DIR}")
include_directories("${CMAKE_BINARY_DIR}/include")

file(GLOB_RECURSE SOURCE_FILES ${PROJECT_SOURCE_DIR}/*.cpp)

#  ____________
# |DEPENDENCIES|
#  ‾‾‾‾‾‾‾‾‾‾‾‾
# SDL2
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})

find_package(SDL2_image REQUIRED)
include_directories(${SDL2_IMAGE_INCLUDE_DIRS})

set(EXTERNAL_LIBS ${SDL2_LIBRARY} ${SDL2_IMAGE_LIBRARY})

include_directories(include)

#  __________
# |EXECUTABLE|
#  ‾‾‾‾‾‾‾‾‾‾
add_executable(motherload ${SOURCE_FILES})
target_link_libraries(motherload ${EXTERNAL_LIBS})

#  _________
# |GAME DATA|
#  ‾‾‾‾‾‾‾‾‾
file(COPY ${CMAKE_BINARY_DIR}/data DESTINATION .)