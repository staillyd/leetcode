project(search)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
add_definitions("-Wall -g")

include_directories(${PROJECT_SOURCE_DIR})

add_executable(binary_search binary_search.cpp)
add_executable(binary_search_1 binary_search_1.cpp)
add_executable(binary_search_2 binary_search_2.cpp)
add_executable(binary_search_3 binary_search_3.cpp)
add_executable(1064 1064.cpp)
add_executable(33 33.cpp)