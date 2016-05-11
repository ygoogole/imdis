cmake_minimum_required(VERSION 3.5)
project(imdis-client)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include_directories(../)
set(SOURCE_FILES
    imdis-client.cpp
    ../TcpHandler.cpp
    ../TcpHandler.h
    ../Common.h
)

#FIND_PACKAGE(Threads REQUIRED)
add_executable(imdis-client ${SOURCE_FILES})
target_link_libraries( imdis-client ${CMAKE_THREAD_LIBS_INIT} )