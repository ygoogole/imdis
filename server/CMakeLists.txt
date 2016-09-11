cmake_minimum_required(VERSION 2.8)
project(imdis-server)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -g")

include_directories(../)

file(GLOB SRCS *.cpp *.h
    ../*.cpp
    ../*.h
    )

#set(SOURCE_FILES
#    imdis-server.cpp
#    ../TcpHandler.cpp
#    ../TcpHandler.h
#    ../Common.h
#    Epoller.cpp
#    Epoller.h
#    Command.cpp
#    Command.h
#    ClientHandler.cpp
#    ClientHandler.h
#    )

FIND_PACKAGE(Threads REQUIRED)
add_executable(imdis-server ${SRCS})
target_link_libraries( imdis-server ${CMAKE_THREAD_LIBS_INIT} )
