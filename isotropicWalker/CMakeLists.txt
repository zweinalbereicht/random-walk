cmake_minimum_required(VERSION 3.10)
project(isotropicWalker)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED YES)

#set(SOURCE_FILES src/GaussianWalker.cpp src/GaussianWalker.h src/BiasedWalker.cpp src/BiasedWalker.h src/SATWWalker.cpp src/SATWWalker.h src/RiemannWalker.h src/RiemannWalker.cpp src/Bindings.cpp src/Observables.cpp src/Observables.h src/GaussianWalker_pcg.h src/GaussianWalker_pcg.cpp ../custom_distributions/Zipf.h ../custom_distributions/Zipf.cpp)

#binding files
set(BINDING_PATH src/bindings/)
set(BINDINGS ${BINDING_PATH}Bindings.cpp ${BINDING_PATH}GaussianWalker_bindings.h ${BINDING_PATH}RTLWalker_bindings.h)# ${BINDING_PATH}Observables_bindings.h)

#walker files
set(WALKER_PATH src/walkers/)
set(WALKERS ${WALKER_PATH}GaussianWalker.h ${WALKER_PATH}GaussianWalker.cpp ${WALKER_PATH}RTLWalker.h ${WALKER_PATH}RTLWalker.cpp)

#Observable files
#set(OBSRVABLE_PATH src/observables/)
#set(OBSRVABLES ${OBSRVABLE_PATH}Observables.h ${OBSRVABLE_PATH}Observables.cpp)

# all source files
set(SOURCE_FILES ../custom_distributions/Zipf/Zipf.h ../custom_distributions/Zipf/Zipf.cpp ${BINDINGS} ${WALKERS})# ${OBSRVABLES})

#set(SOURCE_FILES src/GaussianWalker.cpp src/GaussianWalker.h src/Bindings.cpp src/Observables.cpp src/Observables.h ../pcg-cpp-0.98/include/pcg_test.h)

add_subdirectory(../pybind11 build)
pybind11_add_module(module_isotropicWalker ${SOURCE_FILES})

find_package(GSL REQUIRED)    # See below (2)
target_link_libraries(module_isotropicWalker PUBLIC GSL::gsl GSL::gslcblas)
