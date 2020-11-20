cmake_minimum_required(VERSION 3.17)
project(EpidemicSpreadGraph)

set(CMAKE_CXX_STANDARD 11)


add_executable(EpidemicSpreadGraph src/main.cpp src/Tree.cpp src/Agent.cpp
          src/Session.cpp src/Graph.cpp)
set(CMAKE_CXX_FLAGS "-std=c++11")
