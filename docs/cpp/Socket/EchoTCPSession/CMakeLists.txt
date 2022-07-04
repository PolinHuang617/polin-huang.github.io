cmake_minimum_required(VERSION 3.8)

project(Socket)

set(CMAKE_BUILD_TYPE "Debug")

add_executable(server server.cpp)

add_executable(client client.cpp)
