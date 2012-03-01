project(twilightbin CXX)
cmake_minimum_required(VERSION 2.6)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)

# Build twilight
file(GLOB srcs "*.cc")
add_executable(twilightbin ${srcs})
target_link_libraries(twilightbin twilight EIGEN_LIBRARY)
