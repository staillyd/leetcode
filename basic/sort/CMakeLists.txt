project(sort)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
add_definitions("-Wall -g")

include_directories(${PROJECT_SOURCE_DIR})

add_executable(bobble_sort bobble_sort.cpp )
