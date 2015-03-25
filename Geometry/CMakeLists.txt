project(Geometry C CXX)
file(GLOB CPP_FILES src/*.cpp)
file(GLOB H_FILES include/Geometry/*.h*)

add_library(${PROJECT_NAME} STATIC ${CPP_FILES} ${H_FILES})
set_target_properties(${PROJECT_NAME}
                      PROPERTIES POSITION_INDEPENDENT_CODE ON)


target_link_libraries(${PROJECT_NAME})

set(${PROJECT_NAME}_INCLUDE_DIRS ${PROJECT_SOURCE_DIR}/include
    CACHE INTERNAL "${PROJECT_NAME}: Include Directories" FORCE)
include_directories(${${PROJECT_NAME}_INCLUDE_DIRS})
