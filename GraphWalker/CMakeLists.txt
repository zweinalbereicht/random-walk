cmake_minimum_required(VERSION 3.10)
project(GraphWalker)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED YES)


#binding files
set(BINDING_PATH src/bindings/)
set(BINDINGS ${BINDING_PATH}Bindings.cpp ${BINDING_PATH}Observables_bindings.h ${BINDING_PATH}GraphWalker_bindings.h)

#walker files
set(WALKER_PATH src/walkers/)
set(WALKERS ${WALKER_PATH}GraphWalker.h ${WALKER_PATH}GraphWalker.cpp)

#Observable files
set(OBSRVABLE_PATH src/observables/)
set(OBSRVABLES ${OBSRVABLE_PATH}Observables.h ${OBSRVABLE_PATH}Observables.cpp)

#Graph files
set(GRAPH_PATH ../Graphs/src/include/)
set(GRAPH ${GRAPH_PATH}Graph.h ${GRAPH_PATH}Graph.cpp)

# all source files
set(SOURCE_FILES ../custom_distributions/Zipf/Zipf.h ../custom_distributions/Zipf/Zipf.cpp ${BINDINGS} ${WALKERS} ${OBSRVABLES} ${GRAPH})

add_subdirectory(../pybind11 build)
pybind11_add_module(module_GraphWalker ${SOURCE_FILES})

find_package(GSL REQUIRED)    # See below (2)
target_link_libraries(module_GraphWalker PUBLIC GSL::gsl GSL::gslcblas)
