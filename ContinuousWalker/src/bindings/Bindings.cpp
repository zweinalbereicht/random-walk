#include <iostream>
#include <pybind11/iostream.h>
#include <pybind11/numpy.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <stdlib.h>
#include <string>
#include <vector>

#include "../observables/Observables.h"
#include "../walkers/AlexWalker.h"
#include "../walkers/BiasedWalker.h"
#include "../walkers/ContinuousAdaptativeWalker.h"
#include "../walkers/ContinuousWalker.h"
#include "../walkers/FWalker.h"
#include "../walkers/GammaWalker.h"
#include "../walkers/LaplaceWalker.h"
#include "../walkers/LevyWalker.h"
#include "../walkers/LevyWalkerSkewed.h"
#include "../walkers/ParetoWalker.h"
#include "../walkers/RTPpotentialWalker.h"
#include "../walkers/UniformWalker.h"

using namespace std;
namespace py = pybind11;

PYBIND11_MODULE(ContinuousWalker, handle) {

  handle.doc() = "this is our C++ module for continuous 1 dimensional walkers";

// ContinuousWalker bindings
#include "ContinuousWalker_bindings.h"

// ContinuousWalker bindings
#include "ContinuousAdaptativeWalker_bindings.h"

// Levy walker bindings
#include "LevyWalker_bindings.h"

// Levy walker bindings
#include "LevyWalkerSkewed_bindings.h"

// Laplace walker bindings
#include "LaplaceWalker_bindings.h"

// Gamma walker bindings
#include "GammaWalker_bindings.h"

// Uniform walker bindings
#include "UniformWalker_bindings.h"

// FWalker bindings
#include "FWalker_bindings.h"

// AlexWalker bindings
#include "AlexWalker_bindings.h"

// BiasedWalker bindings
#include "BiasedWalker_bindings.h"

// ParetoWalker bindings
#include "ParetoWalker_bindings.h"

// RTPpotentialWalker bindings
#include "RTPpotentialWalker_bindings.h"

// Observables bindings --> none at the moment
#include "Observables_bindings.h"
}
