cmake_minimum_required(VERSION 2.8.9)
project(collatz-server)

INCLUDE_DIRECTORIES(
  include
)

add_executable(server src/ServerModule.cpp src/FIFOHandler.cpp)
target_link_libraries(server ${YARP_LIBRARIES})
