g++ \
    -std=c++0x \
    -Wall \
    -I /usr/include/eigen3 \
    -lboost_program_options \
    -O3 -o twilight \
    physics.cc numerics.cc date.cc main.cc
