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
#include "../walkers/RiemannWalker.h"
#include "../walkers/SATWWalker.h"

//#include "DiscreteWalker_pcg.h"
#include "../walkers/ZipfWalker.h"

namespace py = pybind11;

py::list
fpt_arrival_bounded_distribution(const long s0,const long N,DiscreteWalker &walker, const int n);

double
fpt_arrival_bounded_probability(const long s0,const long N, const long nbSteps,DiscreteWalker &walker, const int n);

double
survival_bounded_probability(const long s0,const long N, const long nbSteps,DiscreteWalker &walker, const int n);

double
fpt_arrival_bounded_mean(const long s0,const long N,DiscreteWalker &walker, const int n);

double
fpt_arrival_bounded_global_mean(const long N,DiscreteWalker &walker, const int n);

py::list
territory_distribution(const long s0, const long N, DiscreteWalker &walker, const int n);

py::list
territory_distribution_fixed_time_infinite(const long s0, DiscreteWalker &walker, const int nb_steps, const int nb_simus);

py::list
territory_distribution_infinite(const long s0, const long max_steps, DiscreteWalker &walker, const int n);

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

py::list
fpt_arrival_distribution(const long s0, const long max_steps, DiscreteWalker &walker, const int n);

double
splitting_probability(const long s0,const long x, DiscreteWalker &walker, const long N);

py::list
map_of_explored_territory_distribution(const long s0,const long N, DiscreteWalker &walker, const long nb_steps, const long nb_simus);

py::list
territory_discovery_time_distribution(const long s0,const long N, DiscreteWalker &walker, const long nb_steps, const long nb_simus);


py::list
discovery_times_before_cover_time_distribution(const long s0,const long N, DiscreteWalker &walker, const long nb_simus);

py::list
territory_infinite_discovery_time_distribution(const long s0, DiscreteWalker &walker, const long nb_steps, const long nb_simus);

double
cover_time_mean(const long s0, const long N, DiscreteWalker &walker, const int n);

py::list
cover_time_fpt_ratio_distribution(const long s0, DiscreteWalker &walker,const long N, const long nb_simus);
