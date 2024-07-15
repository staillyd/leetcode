project(sort)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
add_definitions("-Wall -g")

include_directories(${PROJECT_SOURCE_DIR})

add_executable(bubble_sort bubble_sort.cpp)
add_executable(insert_sort insert_sort.cpp)
add_executable(shell_sort shell_sort.cpp)
add_executable(select_sort select_sort.cpp)
add_executable(merge_sort merge_sort.cpp)
add_executable(quick_sort quick_sort.cpp)
add_executable(heap_sort heap_sort.cpp)