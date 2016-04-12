file(GLOB_RECURSE SOURCE_FILES *.cpp)
add_library(ED ${SOURCE_FILES})
target_link_libraries(ED wpi)
