cmake_minimum_required(VERSION 3.17)
project(EpidemicSpreadGraph)

set(CMAKE_CXX_STANDARD 14)

add_executable(EpidemicSpreadGraph src/main.cpp)

set(CMAKE_CXX_FLAGS "-std=c++11")