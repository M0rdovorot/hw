cmake_minimum_required(VERSION 3.0.0)
project(hw2 VERSION 0.1.0)

file(GLOB CPPS "src/*.cpp")
add_executable(hw2 ${CPPS})
target_include_directories(hw2 PUBLIC include)