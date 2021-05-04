cmake_minimum_required(VERSION 3.10)
project(RiemannWalker)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED YES)

set(SOURCE_FILES RiemannWalker.cpp RiemannWalker.h)

add_subdirectory(../pybind11 build)
pybind11_add_module(module_RiemannWalker ${SOURCE_FILES})

find_package(GSL REQUIRED)    # See below (2)
target_link_libraries(module_RiemannWalker PUBLIC GSL::gsl GSL::gslcblas)
