#  ____________
# |CMAKE CONFIG|
#  ‾‾‾‾‾‾‾‾‾‾‾‾
cmake_minimum_required(VERSION 3.7)
project(Motherload CXX)

set(CMAKE_BUILD_TYPE debug)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake")
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)

set(PROJECT_SOURCE_DIR ${CMAKE_SOURCE_DIR}/src)
set(PROJECT_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)

#  __________________
# |PLATFORM VARIABLES|
#  ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
if(ARCH STREQUAL "x86")
    SET(PLATFORM_ARCH "x86")
else()
    SET(PLATFORM_ARCH "x64")
endif()

IF(WIN32)
    SET(PLATFORM_PATHS ${CMAKE_SOURCE_DIR}/libraries/windows)
    SET(LIBRARY_EXTENSION "lib")
ELSEIF(APPLE)
    SET(PLATFORM_PATHS ${CMAKE_SOURCE_DIR}/libraries/macos)
    SET(LIBRARY_EXTENSION "dylib")
ELSEIF(UNIX)
    SET(PLATFORM_PATHS ${CMAKE_SOURCE_DIR}/libraries/linux)
    SET(LIBRARY_EXTENSION "so")
ENDIF()

SET(CROSS_PLATFORM_PATHS ${CMAKE_SOURCE_DIR}/libraries/multi)

include_directories(${PROJECT_SOURCE_DIR})
include_directories(${PROJECT_INCLUDE_DIR})

file(GLOB_RECURSE SOURCE_FILES 
    ${PROJECT_SOURCE_DIR}/*.cpp 
    ${PROJECT_INCLUDE_DIR}/*.h)

message("Source dir:" ${PROJECT_SOURCE_DIR})
message("Include dir:" ${PROJECT_INCLUDE_DIR})

#  ____________
# |DEPENDENCIES|
#  ‾‾‾‾‾‾‾‾‾‾‾‾
# SDL2
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})

find_package(GLM REQUIRED)
include_directories(${GLM_INCLUDE_DIR})

set(EXTERNAL_LIBS ${SDL2_LIBRARY} ${GLM_LIBRARY})

include_directories(include)
include_directories(${CROSS_PLATFORM_PATHS}/include)

#  __________
# |EXECUTABLE|
#  ‾‾‾‾‾‾‾‾‾‾
add_executable(motherload ${SOURCE_FILES})
target_link_libraries(motherload ${EXTERNAL_LIBS})

#  _________
# |GAME DATA|
#  ‾‾‾‾‾‾‾‾‾
file(COPY data DESTINATION .)


IF (WIN32)
    SET(SDL2_DLL_FOLDER "${PLATFORM_PATHS}/SDL2/lib/${PLATFORM_ARCH}")

   foreach(flag_var
        CMAKE_CXX_FLAGS CMAKE_CXX_FLAGS_DEBUG CMAKE_CXX_FLAGS_RELEASE
        CMAKE_CXX_FLAGS_MINSIZEREL CMAKE_CXX_FLAGS_RELWITHDEBINFO)
      if(${flag_var} MATCHES "/MD")
        string(REGEX REPLACE "/MD" "/MT" ${flag_var} "${${flag_var}}")
      endif(${flag_var} MATCHES "/MD")
    endforeach(flag_var)

 
    file(GLOB DLLFileList
        "${SDL2_DLL_FOLDER}/*.dll"
    )
 
    file(COPY ${DLLFileList} DESTINATION Debug)
    file(COPY ${DLLFileList} DESTINATION Release)
ENDIF(WIN32)
