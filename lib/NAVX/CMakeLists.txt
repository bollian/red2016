file(GLOB_RECURSE SOURCE_FILES *.cpp)
add_library(NAVX ${SOURCE_FILES})
target_link_libraries(NAVX wpi)
