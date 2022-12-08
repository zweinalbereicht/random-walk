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
split_prob_cone(const double r0, const double theta0, const double theta, GaussianWalker &walker, const int n);

// returns the probability to escape via one side of the cone rather than the otherside (by default we put one side of the cone on the x-axis), and we have reflection on the r=R arc.
double 
split_prob_reflecting_cone(const double r0, const double theta0, const double theta, const double R, GaussianWalker &walker, const int n);

//returns the probability to escape the disk of radius R, centered at 0 and to be located in the arc [theta1, theta2]. For simplicity, the walker always starts at r=R and theta=PI
double 
split_prob_disk_escape(const double R, const double theta1,const double theta2, GaussianWalker &walker, const int n);

// returns the probability to escape concentric discs via the farthest one.
double 
split_prob_concentric_disk(const double R_int,const double R_out, GaussianWalker &walker, const int n);

// returns the probability to escape eccentric discs via the farthest one. We start on the smallest radius whose center is offsetted and with an angle theta0
// wrt to the center of the inner circle
double 
split_prob_eccentric_disk(const double R_int,const double R_out, double const offset, double const theta0, GaussianWalker &walker, const int n);

//returns the probability to survive n steps in a disk of radiius R
double 
survival_disk(const double R, const int nbsteps, GaussianWalker &walker, const int n);

//returns the mean fpt to inner disk with outer disk reflecting
double 
mfpt_2d_disk_outer_reflecting(const double R_int,const double R_out, GaussianWalker &walker, const int n);

// returns a distribution of radial distances when crossing an hyperplane, with respect
// to the projection of the initial distance.
py::list
radial_distance_when_crossing_hyperplan_distribution(const double x0, const double x, GaussianWalker &walker, const int n);

