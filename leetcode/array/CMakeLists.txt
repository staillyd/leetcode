project(array)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
add_definitions("-Wall -g")

include_directories(${PROJECT_SOURCE_DIR})

add_executable(169 169.cpp)
add_executable(26 26.cpp)
add_executable(80 80.cpp)
add_executable(27 27.cpp)
add_executable(3 3.cpp)
add_executable(189 189.cpp)
add_executable(54 54.cpp)
add_executable(1 1.cpp)
add_executable(15 15.cpp)
add_executable(18 18.cpp)
add_executable(16 16.cpp)