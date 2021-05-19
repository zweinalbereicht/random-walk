cmake_minimum_required(VERSION 3.10)
project(ContinuousWalker)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED YES)

set(SOURCE_FILES src/ContinuousWalker.cpp src/ContinuousWalker.h src/LevyWalker.cpp src/LevyWalker.h src/LaplaceWalker.cpp src/LaplaceWalker.h src/GammaWalker.cpp src/GammaWalker.h src/Bindings.cpp)

add_subdirectory(../pybind11 build)
pybind11_add_module(module_ContinuousWalker ${SOURCE_FILES})

find_package(GSL REQUIRED)    # See below (2)
target_link_libraries(module_ContinuousWalker PUBLIC GSL::gsl GSL::gslcblas)
