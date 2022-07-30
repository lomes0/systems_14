cmake_minimum_required(VERSION 3.22)
project(assembler
        VERSION 1.0
        DESCRIPTION "systems 14 project"
        LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB ALL_SOURCES ${PROJECT_SOURCE_DIR}/src/*.cpp)
add_executable(assembler ./src/main.cpp ${ALL_SOURCES})
target_include_directories(assembler PRIVATE "${PROJECT_SOURCE_DIR}/include/")