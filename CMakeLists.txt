cmake_minimum_required (VERSION 3.1 FATAL_ERROR)
project (sixfiveohtwo)

set(CMAKE_BUILD_TYPE RELEASE)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wall -O3 -pthread")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -g -pthread")

# isocharts
file( GLOB SOURCES src/*.cpp )

add_executable(sixfiveohtwo ${SOURCES})
target_include_directories(sixfiveohtwo PUBLIC
  include/)

target_link_libraries(sixfiveohtwo)
