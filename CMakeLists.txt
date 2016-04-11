cmake_minimum_required(VERSION 2.8.11)
project(red2016)

# compiler thingies
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_COMPILER arm-frc-linux-gnueabi-g++)
include_directories(src $ENV{HOME}/wpilib/cpp/current/include)
set(CMAKE_CXX_FLAGS "-std=c++1y -g3 -Wall -O0")
link_directories($ENV{HOME}/wpilib/cpp/current/lib)

# list the files in the project
file(GLOB_RECURSE SOURCE_FILES src/*.cpp src/**.cpp)

add_executable(FRCUserProgram ${SOURCE_FILES})
target_link_libraries(FRCUserProgram wpi)
