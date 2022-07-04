cmake_minimum_required(VERSION 3.08)

project(ASYNC_TCP_UDP_DAYTIME)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_COMPILE_FLAG -pthread)

add_executable(client ./client.cpp)
target_link_libraries(client pthread)

add_executable(server ./server.cpp)
target_link_libraries(server pthread)
