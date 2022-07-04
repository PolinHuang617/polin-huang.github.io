cmake_minimum_required(VERSION 3.8)

project(ParallelCalcTemplate)

set(CMAKE_BUILD_TYPE "Debug")

add_executable(parallelCalc main.cpp)

target_link_libraries(parallelCalc pthread)
