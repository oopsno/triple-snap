cmake_minimum_required(VERSION 3.4)
project(thinmat)

set(CMAKE_CXX_STANDARD 11)
include_directories(include)

file(GLOB ALL_TEST test/*.cpp)
add_executable(unittest ${ALL_TEST})
target_link_libraries(unittest gtest)
