cmake_minimum_required(VERSION 3.10)
project(ContinuousWalker)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED YES)

set(WALKER_PATH src/walkers/)
set(WALKERS ${WALKER_PATH}ContinuousWalker.cpp ${WALKER_PATH}ContinuousWalker.h ${WALKER_PATH}LevyWalker.cpp ${WALKER_PATH}LevyWalker.h ${WALKER_PATH}LaplaceWalker.cpp ${WALKER_PATH}LaplaceWalker.h ${WALKER_PATH}GammaWalker.cpp ${WALKER_PATH}GammaWalker.h ${WALKER_PATH}UniformWalker.cpp ${WALKER_PATH}UniformWalker.h ${WALKER_PATH}FWalker.cpp ${WALKER_PATH}FWalker.h ${WALKER_PATH}AlexWalker.cpp ${WALKER_PATH}AlexWalker.h ${WALKER_PATH}ContinuousAdaptativeWalker.cpp ${WALKER_PATH}ContinuousAdaptativeWalker.h)

set(BINDING_PATH src/bindings/)
set(BINDINGS ${BINDING_PATH}Bindings.cpp ${BINDING_PATH}GammaWalker_bindings.h ${BINDING_PATH}LevyWalker_bindings.h ${BINDING_PATH}ContinuousWalker_bindings.h ${BINDING_PATH}LaplaceWalker_bindings.h ${BINDING_PATH}UniformWalker_bindings.h ${BINDING_PATH}FWalker_bindings.h ${BINDING_PATH}AlexWalker_bindings.h  ${BINDING_PATH}ContinuousAdaptativeWalker_bindings.h ${BINDING_PATH}Observables_bindings.h)

set(OBSERVABLE_PATH src/observables/)
set(OBSERVABLES ${OBSERVABLE_PATH}Observables.cpp ${OBSERVABLE_PATH}Observables.h)

set(SOURCE_FILES ../custom_distributions/Alex/Alex.h ../custom_distributions/Alex/Alex.cpp ${OBSERVABLES} ${BINDINGS} ${WALKERS})

add_subdirectory(../pybind11 build)
pybind11_add_module(module_ContinuousWalker ${SOURCE_FILES})

find_package(GSL REQUIRED)    # See below (2)
target_link_libraries(module_ContinuousWalker PUBLIC GSL::gsl GSL::gslcblas)


