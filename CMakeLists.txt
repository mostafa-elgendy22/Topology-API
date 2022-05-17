cmake_minimum_required(VERSION 3.0.0)
project(topology_api VERSION 1.0.0)


set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${PROJECT_SOURCE_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${PROJECT_SOURCE_DIR}/bin)

include_directories(
    source/
    lib/
    source/component/
    source/resistor/
    source/nmos/
    source/topology/
    source/API/
)

add_subdirectory(source)
add_subdirectory(test)
add_subdirectory(lib/googletest)
