project(twilightsrcs CXX)
cmake_minimum_required(VERSION 2.6)

# Compiler flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x -Wall -Wextra -Werror")

#link_directories(${TWILIGHT_BINARY_DIR}/libtwilight)

# Build libtwilight
add_subdirectory("libtwilight")

# Build idp
add_subdirectory("twilightbin")

