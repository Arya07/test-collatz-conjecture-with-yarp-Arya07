cmake_minimum_required(VERSION 2.8.9)
project(collatz-client)

FIND_PACKAGE(YARP REQUIRED)

set(COMMON_INCLUDE ../common)
INCLUDE_DIRECTORIES(
  include
  ../common
  ${YARP_INCLUDE_DIRS}
)

add_executable(client src/ClientModule.cpp src/CollatzTester.cpp)
target_link_libraries(client ${YARP_LIBRARIES})
