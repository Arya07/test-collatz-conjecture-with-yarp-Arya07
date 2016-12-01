project(collatz-conjecture)

cmake_minimum_required(VERSION 2.8.9)

FIND_PACKAGE(YARP REQUIRED)

INCLUDE_DIRECTORIES(
	common
	${YARP_INCLUDE_DIRS}
)

add_subdirectory(client)
add_subdirectory(server)
