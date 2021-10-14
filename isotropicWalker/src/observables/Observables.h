#pragma once

#include <pybind11/pybind11.h>
#include <pybind11/iostream.h>
#include <pybind11/numpy.h>
#include <pybind11/stl.h>
#include <iostream>
#include <vector>
#include <string>
#include <stdlib.h>

#include "../walkers/GaussianWalker.h"
//#include "../walkers/BiasedWalker.h"
//#include "../walkers/SATWWalker.h"
//#include "../walkers/RiemannWalker.h"
//
////#include "DiscreteWalker_pcg.h"
//#include "../walkers/ZipfWalker.h"

namespace py = pybind11;

// returns the probability to reach the hyperplane x before 0, starting from x0. The default choice of x0 is on the hyperplane
double 
split_prob_hyperplane(const double x0, const double x, GaussianWalker &walker, const int n);
