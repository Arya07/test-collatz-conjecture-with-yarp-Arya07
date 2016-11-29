cmake_minimum_required(VERSION 2.8.9)
project(collatz-server)

FIND_PACKAGE(YARP REQUIRED)

set(COMMON_INCLUDE ../common)
INCLUDE_DIRECTORIES(
  include
  ../common
  ${YARP_INCLUDE_DIRS}
)

add_executable(server src/ServerModule.cpp)
target_link_libraries(server ${YARP_LIBRARIES})
