cmake_minimum_required(VERSION 3.8)

project(ASYNC_TCP_Daytime)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_COMPILE_FALG -pthread)

add_executable(client ./client.cpp)
target_link_libraries(client pthread)

add_executable(server ./server.cpp)
target_link_libraries(server pthread)
