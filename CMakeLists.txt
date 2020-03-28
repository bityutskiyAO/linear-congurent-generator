cmake_minimum_required(VERSION 3.15)
project(untitled)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

add_executable(paralel-lab1 main.cpp LCG.cpp LCG.h GeneratorEvaluation.cpp GeneratorEvaluation.h)