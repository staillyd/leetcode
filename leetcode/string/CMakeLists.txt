project(string)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
add_definitions("-Wall -g")

include_directories(${PROJECT_SOURCE_DIR})

add_executable(3_string 3.cpp)
add_executable(76 76.cpp)
add_executable(14 14.cpp)
add_executable(345 345.cpp)
