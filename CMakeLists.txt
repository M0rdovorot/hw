cmake_minimum_required(VERSION 3.0.0)
project(hw11 VERSION 0.1.0)

add_executable(hw11 src/main.cpp src/foo.cpp)
target_include_directories(hw11 PUBLIC include)