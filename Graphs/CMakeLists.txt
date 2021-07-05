cmake_minimum_required(VERSION 3.10)
project(Graphs)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED YES)


#tool files
set(INCLUDE_PATH src/include/)
set(INCLUDE_FILES ${INCLUDE_PATH}Graph.h ${INCLUDE_PATH}Graph.cpp)
#set(TOOL_FILES ${INCLUDE_PATH}tools.h ${INCLUDE_PATH}tools.c)

# all source files
#set(SOURCE_FILES ${INCLUDE_FILES} ${TOOL_FILES})
set(SOURCE_FILES ${INCLUDE_FILES})

#executable files
set(EXECUTABLE_PATH src/executables/)
add_executable(create_all_files ${EXECUTABLE_PATH}create_all_files.cpp ${SOURCE_FILES})
add_executable(make_chemdist_from_SP ${EXECUTABLE_PATH}make_chemdist_from_SP.cpp ${SOURCE_FILES})

#add_executable(make_percolation_graph ${EXECUTABLE_PATH}make_percolation_graph.c ${SOURCE_FILES})

##required library
#find_package(GSL REQUIRED)    # See below (2)
#target_include_directories(make_percolation_graph PRIVATE ${PROJECT_SOURCE_DIR} ${GSL_INCLUDE_DIR})
#target_link_libraries(make_percolation_graph PUBLIC GSL::gsl GSL::gslcblas)

