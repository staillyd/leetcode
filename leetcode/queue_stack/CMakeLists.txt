project(queue_stack)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 ")
add_definitions("-Wall -g")

include_directories(${PROJECT_SOURCE_DIR})

add_executable(42 42.cpp)
add_executable(239 239.cpp)