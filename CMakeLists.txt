project(DataStructures)
set(CMAKE_C_COMPILER gcc)
set(CMAKE_C_FLAGS "-std=c99 -O3")
cmake_minimum_required(VERSION 2.8)
aux_source_directory(. SRC_LIST)
aux_source_directory(vector SRC_LIST)
add_executable(${PROJECT_NAME} ${SRC_LIST})

