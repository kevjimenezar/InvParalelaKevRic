cmake_minimum_required(VERSION 3.21)
project(InvProyecto)

set(CMAKE_CXX_STANDARD 14)

add_executable(InvProyecto main.cpp)


find_package(OpenMP REQUIRED)
if(OpenMP_CXX_FOUND)
    target_link_libraries(InvProyecto PRIVATE OpenMP::OpenMP_CXX)
endif()
