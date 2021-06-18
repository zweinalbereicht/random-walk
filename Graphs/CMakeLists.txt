cmake_minimum_required(VERSION 3.10)
project(Graphs)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED YES)

#tool files
set(INCLUDE_PATH src/include/)
set(INCLUDE_FILES ${INCLUDE_PATH}Graph.h ${INCLUDE_PATH}Graph.cpp)

# all source files
set(SOURCE_FILES ${INCLUDE_FILES})

#executable files
set(EXECUTABLE_PATH src/executables/)
add_executable(create_all_files ${EXECUTABLE_PATH}create_all_files.cpp ${SOURCE_FILES})
