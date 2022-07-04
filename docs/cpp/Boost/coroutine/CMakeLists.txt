cmake_minimum_required(VERSION 3.8)

project(BoostCorotine)

set(CMAKE_BUILD_TYPE "Debug")

find_package(Boost REQUIRED)
if(Boost_FOUND)
	include_directories(${Boost_INCLUDE_DIRS})
	set(CMAKE_CXX_FLAGS "-std=c++11 -lboost_corotine2 -lboost_context")

	MESSAGE( STATUS "Boost_INCLUDE_DIRS = ${Boost_INCLUDE_DIRS}." )
	MESSAGE( STATUS "Boost_LIBRARY_DIRS = ${Boost_LIBRARY_DIRS}." )
	MESSAGE( STATUS "Boost_LIBRARIES = ${Boost_LIBRARIES}." )
	MESSAGE( STATUS "Boost_LIB_VERSION = ${Boost_LIB_VERSION}." )

	add_executable(boostCorotine main.cpp)

	target_link_libraries(boostCorotine ${Boost_LIBRARIES})
endif()
