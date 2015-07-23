cmake_minimum_required(VERSION 3.1)
project(real_assignment)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp)
add_executable(real_assignment ${SOURCE_FILES} Messages.h Message.h Packet.h)