project(Executables)
include_directories(
    ${Engine_INCLUDE_DIRS}
    ${Geometry_INCLUDE_DIRS}
    ${Utils_INCLUDE_DIRS}
    ${Model_INCLUDE_DIRS}
    ${Server_INCLUDE_DIRS}
    ${TCPConnection_INCLUDE_DIRS}
    ${Thread_INCLUDE_DIRS}
)
add_executable(engineEx engine.cpp)

target_link_libraries(engineEx Engine )

add_executable(ServerEx server.cpp)
target_link_libraries(ServerEx Server TCPConnection Thread mlpack Utils Engine )


add_executable(ClientEx client.cpp)
target_link_libraries(ClientEx Model mlpack Utils TCPConnection)

add_executable(TestEx test.cpp)
target_link_libraries(TestEx Model mlpack Utils TCPConnection)
