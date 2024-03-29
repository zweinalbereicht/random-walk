#include <iostream>
#include <pybind11/iostream.h>
#include <pybind11/numpy.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <stdlib.h>
#include <string>
#include <vector>

//#include "../../pcg-cpp-0.98/include/pcg_random_walk.h"

#include "../walkers/DiscreteWalker.h"
#include "../walkers/ZipfWalker.h"
//#include "DiscreteWalker_pcg.h"
//#include "../walkers/BiasedWalker.h"
//#include "../walkers/SATWWalker.h"
//#include "../walkers/RiemannWalker.h"
//#include "../walkers/ZipfWalker.h"
//
#include "../observables/Observables.h" //specific histogram creations

namespace py = pybind11;
using namespace std;

PYBIND11_MAKE_OPAQUE(vector<long>);

PYBIND11_MODULE(d_dimDiscreteWalker, handle) {

  handle.doc() = "this is our C++ module for discrete d dimensional walkers";

// DiscreteWalker bindings
#include "DiscreteWalker_bindings.h"

  // //Biased walker bindings
  // #include "BiasedWalker_bindings.h"

  // //SATW walker bindings
  // #include "SATWWalker_bindings.h"

  // //Riemann walker bindings
  // #include "RiemannWalker_bindings.h"

// ZipfWalker bindings
#include "ZipfWalker_bindings.h"

  // // Discrete Walker PCG implementation bindings
  // //#include "DiscreteWalker_pcg_bindings.h"

  // // these methods will be for very specific usecases, such as providing data
  // for histograms for instance
#include "Observables_bindings.h"
}
