project(dp)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 ")
add_definitions("-Wall -g")

include_directories(${PROJECT_SOURCE_DIR})

add_executable(279 279.cpp)
add_executable(322 322.cpp)