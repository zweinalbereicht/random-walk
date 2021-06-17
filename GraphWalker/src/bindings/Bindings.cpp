#include <pybind11/pybind11.h>
#include <pybind11/iostream.h>
#include <pybind11/numpy.h>
#include <pybind11/stl.h>
#include <iostream>
#include <vector>
#include <string>
#include <stdlib.h>

//#include "../../pcg-cpp-0.98/include/pcg_random_walk.h"

#include "../walkers/GraphWalker.h"

#include "../observables/Observables.h" //specific histogram creations

namespace py = pybind11;
using namespace std;

PYBIND11_MODULE(module_GraphWalker,handle){

    handle.doc()="this is our C++ module for generic random walkers on graphs";

    // GraphWalker bindings
    #include "GraphWalker_bindings.h"

    // these methods will be for very specific usecases, such as providing data for histograms for instance
    #include "Observables_bindings.h"

}
