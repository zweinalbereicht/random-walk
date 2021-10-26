#include <iostream>
#include <string>
#include <vector>
#include <pybind11/pybind11.h>
#include <stdlib.h>

#include "../walkers/ContinuousWalker.h"
#include "../walkers/LevyWalker.h"
#include "../walkers/LaplaceWalker.h"
#include "../walkers/GammaWalker.h"
#include "../walkers/FWalker.h"
#include "../walkers/AlexWalker.h"
#include "../walkers/UniformWalker.h"
#include "../observables/Observables.h"

using namespace std;
namespace py = pybind11;

PYBIND11_MODULE(module_ContinuousWalker,handle){

    handle.doc()="this is our C++ module for continuous 1 dimensional walkers";

    //ContinuousWalker bindings
    #include "ContinuousWalker_bindings.h"

    //Levy walker bindings
    #include "LevyWalker_bindings.h"

    //Laplace walker bindings
    #include "LaplaceWalker_bindings.h"
    
    //Gamma walker bindings
    #include "GammaWalker_bindings.h"

    //Uniform walker bindings
    #include "UniformWalker_bindings.h"

    //FWalker bindings
    #include "FWalker_bindings.h"

    //AlexWalker bindings
    #include "AlexWalker_bindings.h"

    //Observables bindings --> none at the moment
    #include "Observables_bindings.h"

}

