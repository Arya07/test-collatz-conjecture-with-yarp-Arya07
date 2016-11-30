cmake_minimum_required(VERSION 2.8.9)
project(collatz-client)

INCLUDE_DIRECTORIES(
  include
)

add_executable(client src/ClientModule.cpp src/CollatzTester.cpp)
target_link_libraries(client ${YARP_LIBRARIES})
