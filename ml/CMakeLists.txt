project(ml)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x -fopenmp")
add_definitions("-Wall -g")

include_directories(${PROJECT_SOURCE_DIR})

# set(THREADS_PREFER_PTHREAD_FLAG ON)
# find_package(Threads REQUIRED)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

SET( EIGEN3_INCLUDE_DIR "$ENV{EIGEN3_INCLUDE_DIR}" )
find_package( Eigen3 3.3 REQUIRED )
include_directories( ${EIGEN3_INCLUDE_DIR} )

add_executable(tmp tmp.cpp )
# target_link_libraries(tmp PRIVATE Threads::Threads)

add_executable(fit_line fit_line.cpp )
# target_link_libraries(fit_line ${OpenCV_LIBS})

add_executable(kmeans kmeans.cpp)
add_executable(dbscan dbscan.cpp)

