project(libtwilight CXX)
cmake_minimum_required(VERSION 2.6)

# Build libtwilight
file(GLOB srcs "*.cc")
add_library(twilight STATIC ${srcs})
