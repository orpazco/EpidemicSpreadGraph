cmake_minimum_required(VERSION 3.17)
project(EpidemicSpreadGraph)

set(CMAKE_CXX_STANDARD 11)


add_executable(EpidemicSpreadGraph src/origMain.cpp src/main.cpp src/Tree.cpp src/Agent.cpp test/src/TreeTests.cpp
        test/include/TreeTests.h test/src/TestMain.cpp test/include/TestMain.h test/src/testsMain.cpp
        test/src/CreateTree.cpp test/include/CreateTree.h src/Session.cpp src/Graph.cpp test/src/SessionTests.cpp test/include/SessionTests.h
        AutoTests/FiveRuleTestTree.cpp AutoTests/Main.cpp AutoTests/Tester.cpp AutoTests/Tester.h)
set(CMAKE_CXX_FLAGS "-std=c++11")
