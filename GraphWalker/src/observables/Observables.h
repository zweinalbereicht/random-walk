#pragma once

#include <pybind11/pybind11.h>
#include <pybind11/iostream.h>
#include <pybind11/numpy.h>
#include <pybind11/stl.h>
#include <iostream>
#include <vector>
#include <string>
#include <stdlib.h>

#include "../walkers/GraphWalker.h"

namespace py = pybind11;

py::list
fpt_arrival_distribution(const int s0,const int target,GraphWalker &walker, const int n);

double
fpt_arrival_mean(const int s0,const int target,GraphWalker &walker, const int n);

double
fpt_arrival_global_mean(const int target,GraphWalker &walker, const int n);

py::list
territory_distribution(const int s0, const int target, GraphWalker &walker, const int n);

double
territory_mean(const int s0, const int target , GraphWalker &walker, const int n);

double
territory_global_mean(const int target, GraphWalker &walker, const int n);
