cmake_minimum_required(VERSION 2.8.9)
set(PROJECTNAME collatzServer)
project(${PROJECTNAME})

INCLUDE_DIRECTORIES(
  include
)

add_executable(${PROJECTNAME} src/ServerModule.cpp src/FIFOHandler.cpp)
target_link_libraries(${PROJECTNAME} ${YARP_LIBRARIES})
