cmake_minimum_required(VERSION 3.3.2)
project(City_map)

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
add_definitions("-std=c++11")

#Bring the headers into the project
include_directories(include)

#List of executables
file(GLOB SOURCES "src/*.cpp")

add_executable(solution ${SOURCES})
