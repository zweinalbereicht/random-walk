cmake_minimum_required(VERSION 3.10)
project(DiscreteWalker)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED YES)

set(SOURCE_FILES DiscreteWalker.cpp DiscreteWalker.h BiasedWalker.cpp BiasedWalker.h SATWWalker.cpp SATWWalker.h Bindings.cpp)

add_subdirectory(../pybind11 build)
pybind11_add_module(module_DiscreteWalker ${SOURCE_FILES})

find_package(GSL REQUIRED)    # See below (2)
target_link_libraries(module_DiscreteWalker PUBLIC GSL::gsl GSL::gslcblas)
