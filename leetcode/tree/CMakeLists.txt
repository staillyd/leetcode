project(tree)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
add_definitions("-Wall -g")

include_directories(${PROJECT_SOURCE_DIR})

add_executable(144 144.cpp)
add_executable(145 145.cpp)
add_executable(94 94.cpp)
add_executable(102 102.cpp)