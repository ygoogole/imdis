cmake_minimum_required(VERSION 3.5)
project(imdis-server)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include_directories(../)

set(SOURCE_FILES
    imdis-server.cpp
    ../TcpHandler.cpp
    ../TcpHandler.h
    ../Common.h
    Epoller.cpp
    Epoller.h
)

FIND_PACKAGE(Threads REQUIRED)
add_executable(imdis-server ${SOURCE_FILES})
target_link_libraries( imdis-server ${CMAKE_THREAD_LIBS_INIT} )