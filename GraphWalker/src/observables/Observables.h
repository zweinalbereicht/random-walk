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
#include "../walkers/Graph.h"

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

//same as above but with a time limit
py::list
territory_fixed_time_distribution(const int s0, const int target, GraphWalker &walker,const int max_time, const int n);

double
territory_fixed_time_mean(const int s0, const int target , GraphWalker &walker,const int max_time, const int n);

double
territory_fixed_time_global_mean(const int target, GraphWalker &walker,const int max_time, const int n);

py::list
max_dist_territory_distribution(const int s0, const int target, GraphWalker &walker,const int n,const string filename);

py::list
position_distribution(const int s0, const int steps, GraphWalker &walker, const int n);
