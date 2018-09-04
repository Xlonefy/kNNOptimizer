cmake_minimum_required(VERSION 3.5.0)
project(Learn)

find_package(OpenMP)
if (OPENMP_FOUND)
    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
    set (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
endif()

find_package(Eigen3 3.3 REQUIRED NO_MODULE)

add_definitions(-Wall -Wextra -Wpedantic -std=c++17 -O4 -march=native)

include_directories(include)
file(GLOB SOURCES "src/*.cpp")
add_library(Learn SHARED ${SOURCES})
target_link_libraries(Learn Eigen3::Eigen)

add_executable(main main.cc)
target_link_libraries(main Learn)
