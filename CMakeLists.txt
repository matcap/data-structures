project(DataStructures)
set(CMAKE_C_COMPILER gcc)
set(CMAKE_C_FLAGS "-std=c99 -pedantic -Wall -O0 ")
cmake_minimum_required(VERSION 2.8)

aux_source_directory(. SRC_LIST)
aux_source_directory(vector SRC_LIST)
aux_source_directory(list SRC_LIST)

add_executable(${PROJECT_NAME} ${SRC_LIST})

