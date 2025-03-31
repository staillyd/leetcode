project(ml)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
add_definitions("-Wall -g")

include_directories(${PROJECT_SOURCE_DIR})

# set(THREADS_PREFER_PTHREAD_FLAG ON)
# find_package(Threads REQUIRED)

# find_package(OpenCV REQUIRED)
# include_directories(${OpenCV_INCLUDE_DIRS})
# add_definitions(${OpenCV_DEFINITIONS})
# link_directories(${OpenCV_LIBRARY_DIRS})

SET( EIGEN3_INCLUDE_DIR "$ENV{EIGEN3_INCLUDE_DIR}" )
find_package( Eigen3 3.3 REQUIRED )
include_directories( ${EIGEN3_INCLUDE_DIR} )

add_executable(tmp tmp.cpp )
# target_link_libraries(tmp PRIVATE Threads::Threads)

add_executable(fit_line fit_line.cpp )
# target_link_libraries(fit_line ${OpenCV_LIBS})

add_executable(kmeans kmeans.cpp)
add_executable(dbscan dbscan.cpp)
add_executable(ransac ransac.cpp)
add_executable(bilinear_interpolation bilinear_interpolation.cpp)
add_executable(project_3d_to_2d project_3d_to_2d.cpp)
add_executable(nms nms.cpp)
add_executable(shared_ptr shared_ptr.cpp)

# find_package(PCL 1.10 REQUIRED COMPONENTS )
# include_directories(${PCL_INCLUDE_DIRS})
# add_definitions(${PCL_DEFINITIONS})
# link_directories(${PCL_LIBRARY_DIRS})

# find_package(Sophus REQUIRED)
# include_directories(${Sophus_INCLUDE_DIRS})
# add_definitions(${Sophus_DEFINITIONS})
# link_directories(${Sophus_LIBRARY_DIRS})

# find_package(Ceres REQUIRED)
# include_directories(${CERES_INCLUDE_DIRS})
# add_definitions(${CERES_DEFINITIONS})
# link_directories(${CERES_LIBRARY_DIRS})

# add_executable(icp icp.cpp)
# target_link_libraries(icp ${PCL_LIBRARIES})
# target_link_libraries(icp ${Sophus_LIBRARIES})
# target_link_libraries(icp ${CERES_LIBRARIES})
# target_link_libraries(icp ${OpenCV_LIBRARIES})