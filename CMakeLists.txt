cmake_minimum_required(VERSION 2.8)
project( TestGMM )
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DCGAL_DISABLE_ROUNDING_MATH_CHECK")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall")
aux_source_directory(. SRC_LIST)
add_executable(prog ${SRC_LIST})
include_directories(/usr/include/libxml2)
target_link_libraries( prog mlpack armadillo CGAL gmp mpfr pugixml)

