project(twilight CXX)
cmake_minimum_required(VERSION 2.6)

# Do not allow builds inside the source tree
#if("${TWILIGHT_SOURCE_DIR}" STREQUAL "${TWILIGHT_BINARY_DIR}")
#message(FATAL_ERROR "Builds inside the source tree are not allowed.")
#endif()

# Set debug/release
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release")
endif(NOT CMAKE_BUILD_TYPE)

# Compiler flags
if("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")
endif()

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
find_package(Eigen)

include_directories(
    "${TWILIGHT_SOURCE_DIR}/src"
    "${EIGEN_INCLUDE_DIRS}"
)

# Build twilight
add_subdirectory("src")
