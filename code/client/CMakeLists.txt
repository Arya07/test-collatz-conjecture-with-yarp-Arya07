cmake_minimum_required(VERSION 2.8.9)
set(PROJECTNAME collatzClient)
project(${PROJECTNAME})

INCLUDE_DIRECTORIES(
  include
)

add_executable(${PROJECTNAME} src/ClientModule.cpp src/CollatzTester.cpp)
target_link_libraries(${PROJECTNAME} ${YARP_LIBRARIES})
