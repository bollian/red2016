cmake_minimum_required(VERSION 2.8.11)
project(red2016)

# compiler thingies
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_COMPILER arm-frc-linux-gnueabi-g++)
include_directories(src lib $ENV{HOME}/wpilib/cpp/current/include)
set(CMAKE_CXX_FLAGS "-std=c++1y -g3 -Wall -O0 -Wl,-rpath,/opt/GenICam_v2_3/bin/Linux_armv7-a,-rpath,/usr/local/frc/rpath-lib")
link_directories($ENV{HOME}/wpilib/cpp/current/lib lib/NAVX lib/ED)

add_subdirectory(lib/NAVX)
add_subdirectory(lib/ED)

# list the files in the project
file(GLOB_RECURSE SOURCE_FILES src/*.cpp src/**.cpp)

add_executable(FRCUserProgram ${SOURCE_FILES})
target_link_libraries(FRCUserProgram wpi NAVX ED)
