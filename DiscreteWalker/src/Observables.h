#pragma once

#include <pybind11/pybind11.h>
#include <pybind11/iostream.h>
#include <pybind11/numpy.h>
#include <pybind11/stl.h>
#include <iostream>
#include <vector>
#include <string>
#include <stdlib.h>

#include "DiscreteWalker.h"
#include "BiasedWalker.h"
#include "SATWWalker.h"
#include "RiemannWalker.h"

//#include "DiscreteWalker_pcg.h"
#include "ZipfWalker.h"

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
