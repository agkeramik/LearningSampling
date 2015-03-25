cmake_minimum_required(VERSION 2.8)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall")
#folders that contains the libraries
add_subdirectory(Engine)
add_subdirectory(Model)
add_subdirectory(Server)
add_subdirectory(TCPConnection)
add_subdirectory(Thread)
add_subdirectory(Utils)
add_subdirectory(Geometry)

#folder that contains all the executables
add_subdirectory(Executables)
