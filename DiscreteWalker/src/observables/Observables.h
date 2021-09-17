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
#include "../walkers/BiasedWalker.h"
#include "../walkers/SATWWalker.h"
#include "../walkers/RiemannWalker.h"

//#include "DiscreteWalker_pcg.h"
#include "../walkers/ZipfWalker.h"

namespace py = pybind11;

py::list
fpt_arrival_bounded_distribution(const long s0,const long N,DiscreteWalker &walker, const int n);

double
fpt_arrival_bounded_mean(const long s0,const long N,DiscreteWalker &walker, const int n);

double
fpt_arrival_bounded_global_mean(const long N,DiscreteWalker &walker, const int n);

py::list
territory_distribution(const long s0, const long N, DiscreteWalker &walker, const int n);

double
territory_mean(const long s0, const long N, DiscreteWalker &walker, const int n);

double
territory_global_mean(const long N, DiscreteWalker &walker, const int n);

double
rosenstock_fixed_time(const long s0, DiscreteWalker &walker, const int time, const double rho, const int n,const int verbose=0);

py::list
conditional_fpt_distribution(const long s0,const long x, DiscreteWalker &walker, const long N,const bool target=1);

double
conditional_fpt_mean(const double s0,const double x, DiscreteWalker &walker, const long N,const bool target=1);

double
survival_probability(const long s0,const long n, DiscreteWalker &walker, const long N);

double
splitting_probability(const long s0,const double x, DiscreteWalker &walker, const long N);
