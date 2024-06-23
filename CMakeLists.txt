project(leetcode)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
add_definitions("-Wall -g")

add_subdirectory(basic/sort)
add_subdirectory(basic/search)
add_subdirectory(leetcode/array)
add_subdirectory(leetcode/string)
add_subdirectory(leetcode/chain)
add_subdirectory(leetcode/tree)
add_subdirectory(ml)
