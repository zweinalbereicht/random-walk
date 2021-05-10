cmake_minimum_required(VERSION 3.10)
project(ContinuousWalker)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED YES)

set(SOURCE_FILES ContinuousWalker.cpp ContinuousWalker.h LevyWalker.cpp LevyWalker.h LaplaceWalker.cpp LaplaceWalker.h GammaWalker.cpp GammaWalker.h)

add_subdirectory(../pybind11 build)
pybind11_add_module(module_ContinuousWalker ${SOURCE_FILES})

find_package(GSL REQUIRED)    # See below (2)
target_link_libraries(module_ContinuousWalker PUBLIC GSL::gsl GSL::gslcblas)
