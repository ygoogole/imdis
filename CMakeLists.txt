cmake_minimum_required(VERSION 3.5)
project(imdis)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

add_subdirectory(server)
add_subdirectory(client)

SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
SET(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)

#set(SOURCE_FILES TcpHandler.cpp TcpHandler.h Common.h)

#FIND_PACKAGE(Threads REQUIRED)
#add_executable(imdis ${SOURCE_FILES})
#target_link_libraries( imdis ${CMAKE_THREAD_LIBS_INIT} )
