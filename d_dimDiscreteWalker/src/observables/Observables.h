#pragma once

#include <pybind11/pybind11.h>
#include <pybind11/iostream.h>
#include <pybind11/numpy.h>
#include <pybind11/stl.h>
#include <iostream>
#include <vector>
#include <string>
#include <stdlib.h>

#include "../walkers/DiscreteWalker.h"
//#include "../walkers/BiasedWalker.h"
//#include "../walkers/SATWWalker.h"
//#include "../walkers/RiemannWalker.h"
//
////#include "DiscreteWalker_pcg.h"
//#include "../walkers/ZipfWalker.h"

namespace py = pybind11;

py::list
fpt_arrival_bounded_distribution(const pybind11::list &s0,const pybind11::list &dimensions,DiscreteWalker &walker, const int n);

double
fpt_arrival_bounded_mean(const pybind11::list &s0,const pybind11::list &dimensions,DiscreteWalker &walker, const int n);

double
fpt_arrival_bounded_global_mean(const pybind11::list &dimensions,DiscreteWalker &walker, const int n);

py::list
territory_distribution(const pybind11::list &s0, const pybind11::list &dimensions, DiscreteWalker &walker, const int n);

double
territory_global_mean(const pybind11::list &dimensions, DiscreteWalker &walker, const int n);

double
territory_mean(const pybind11::list &s0, const pybind11::list &dimensions, DiscreteWalker &walker, const int n);

py::list
territory_unbounded_fixed_time_distribution(const pybind11::list &s0, DiscreteWalker &walker, const int max_time,const int n);

py::list
fpt_unbounded_fixed_time_distribution(const pybind11::list &s0, DiscreteWalker &walker, const int max_time,const int n);

double
territory_unbounded_fixed_time_mean(const pybind11::list &s0, DiscreteWalker &walker, const int max_time, const int n);

double
rosenstock_fixed_time(const long s0, DiscreteWalker &walker, const int time, const double rho, const int n);

py::list
cover_time_distribution(const pybind11::list &dimensions, const pybind11::list &s0, DiscreteWalker &walker, const int max_time, const int n);

py::list
discovery_times_before_cover_distribution(const pybind11::list &dimensions, const pybind11::list &s0, DiscreteWalker &walker, const int n);
