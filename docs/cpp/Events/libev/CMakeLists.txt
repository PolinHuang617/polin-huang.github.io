cmake_minimum_required(VERSION 3.8)

project(LIBEV_TEST)

set(CMAKE_CXX_STANDARD 11)

include_directories(deps/libev)
link_directories(deps/libev/.libs)

add_executable(io-signal-timeout ./io-signal-timeout.cpp)
target_link_libraries(io-signal-timeout libev.so)

add_executable(fd-listener ./fd-listener.cpp)
target_link_libraries(io-signal-timeout libev.so)

add_executable(async async.cpp)
target_link_libraries(test libev.so pthread)
