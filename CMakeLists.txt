cmake_minimum_required(VERSION 3.5)
project(imdis)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES imdis-server.cpp TcpHandler.cpp TcpHandler.h Common.h)
add_executable(imdis ${SOURCE_FILES})
