cmake_minimum_required(VERSION 3.10)
project(DiscreteWalker)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED YES)

#set(SOURCE_FILES src/DiscreteWalker.cpp src/DiscreteWalker.h src/BiasedWalker.cpp src/BiasedWalker.h src/SATWWalker.cpp src/SATWWalker.h src/RiemannWalker.h src/RiemannWalker.cpp src/Bindings.cpp src/Observables.cpp src/Observables.h src/DiscreteWalker_pcg.h src/DiscreteWalker_pcg.cpp ../custom_distributions/Zipf.h ../custom_distributions/Zipf.cpp)

#binding files
set(BINDING_PATH src/bindings/)
set(BINDINGS ${BINDING_PATH}Bindings.cpp ${BINDING_PATH}Observables_bindings.h)

#walker files
set(WALKER_PATH src/walkers/)
set(WALKERS ${WALKER_PATH}DiscreteWalker.h ${WALKER_PATH}DiscreteWalker.cpp ${WALKER_PATH}SATWWalker.h ${WALKER_PATH}SATWWalker.cpp ${WALKER_PATH}ZipfWalker.h ${WALKER_PATH}ZipfWalker.cpp ${WALKER_PATH}BiasedWalker.h ${WALKER_PATH}BiasedWalker.cpp ${WALKER_PATH}RiemannWalker.h ${WALKER_PATH}RiemannWalker.cpp)

#Observable files
set(OBSRVABLE_PATH src/observables/)
set(OBSRVABLES ${OBSRVABLE_PATH}Observables.h ${OBSRVABLE_PATH}Observables.cpp)

# all source files
set(SOURCE_FILES ../custom_distributions/Zipf/Zipf.h ../custom_distributions/Zipf/Zipf.cpp ${BINDINGS} ${WALKERS} ${OBSRVABLES})

#set(SOURCE_FILES src/DiscreteWalker.cpp src/DiscreteWalker.h src/Bindings.cpp src/Observables.cpp src/Observables.h ../pcg-cpp-0.98/include/pcg_test.h)

add_subdirectory(../pybind11 build)
pybind11_add_module(module_DiscreteWalker ${SOURCE_FILES})

find_package(GSL REQUIRED)    # See below (2)
target_link_libraries(module_DiscreteWalker PUBLIC GSL::gsl GSL::gslcblas)
