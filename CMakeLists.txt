cmake_minimum_required(VERSION 3.20)
project(CarSimLocal)

set(CMAKE_CXX_STANDARD 17)

add_executable(CarSimLocal main.cpp src/Plant.cpp include/Plant.h src/Path.cpp include/Path.h)
