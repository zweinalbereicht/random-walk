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

// returns the probability to escape via one side of the cone rather than the otherside (by default we put one side of the cone on the x-axis)
double 
split_prob_cone(const double x0, const double theta, GaussianWalker &walker, const int n);

// returns a distribution of radial distances when crossing an hyperplane, with respect
// to the projection of the initial distance.
py::list
radial_distance_when_crossing_hyperplan_distribution(const double x0, const double x, GaussianWalker &walker, const int n);

