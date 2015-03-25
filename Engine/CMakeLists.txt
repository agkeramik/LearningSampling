project(Engine C CXX)
file(GLOB CPP_FILES src/*.cpp)
file(GLOB H_FILES include/Engine/*.h*)

add_library(${PROJECT_NAME} STATIC ${CPP_FILES} ${H_FILES})
set_target_properties(${PROJECT_NAME}
                      PROPERTIES POSITION_INDEPENDENT_CODE ON)
target_link_libraries(${PROJECT_NAME} mlpack armadillo pugixml Geometry Utils Model)

set(${PROJECT_NAME}_INCLUDE_DIRS ${PROJECT_SOURCE_DIR}/include
    /usr/include/libxml2
    ${Geometry_INCLUDE_DIRS}
    ${Utils_INCLUDE_DIRS}
    ${Model_INCLUDE_DIRS}
    CACHE INTERNAL "${PROJECT_NAME}: Include Directories" FORCE)
include_directories(${${PROJECT_NAME}_INCLUDE_DIRS})
