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

namespace py = pybind11;

py::list arrival_fpt_bounded(const long s0,const long N,DiscreteWalker &walker, const int n);

double global_mean_arrival_fpt_bounded(long N,DiscreteWalker &walker, const int n);

double mean_arrival_fpt_bounded(long s0,long N,DiscreteWalker &walker, const int n);
