cmake_minimum_required(VERSION 3.8)

project(libhv-tutorial)

set(CMAKE_BUILD_TYPE "Debug")
# set(CMAKE_BUILD_TYPE "Release")

include_directories(deps/libhv/build/include)
link_directories(deps/libhv/build/lib)

add_executable(server server.cpp)
target_link_libraries(server hv pthread)

add_executable(syncClient syncClient.cpp)
target_link_libraries(syncClient hv pthread)

add_executable(asyncClient asyncClient.cpp)
target_link_libraries(asyncClient hv pthread)