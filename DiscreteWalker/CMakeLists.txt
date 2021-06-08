cmake_minimum_required(VERSION 3.10)
project(DiscreteWalker)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED YES)

set(SOURCE_FILES src/DiscreteWalker.cpp src/DiscreteWalker.h src/BiasedWalker.cpp src/BiasedWalker.h src/SATWWalker.cpp src/SATWWalker.h src/RiemannWalker.h src/RiemannWalker.cpp src/Bindings.cpp src/Observables.cpp src/Observables.h src/DiscreteWalker_pcg.h src/DiscreteWalker_pcg.cpp)
#set(SOURCE_FILES src/DiscreteWalker.cpp src/DiscreteWalker.h src/Bindings.cpp src/Observables.cpp src/Observables.h ../pcg-cpp-0.98/include/pcg_test.h)

add_subdirectory(../pybind11 build)
pybind11_add_module(module_DiscreteWalker ${SOURCE_FILES})

find_package(GSL REQUIRED)    # See below (2)
target_link_libraries(module_DiscreteWalker PUBLIC GSL::gsl GSL::gslcblas)
