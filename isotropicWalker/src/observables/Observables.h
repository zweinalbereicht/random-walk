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

// distribution of arrival times in offsetted inner target, with reflecting outer target.
py::list
fpt_distribution_eccentric_inner_disk_outer_reflecting(const double R_int,const double R_out, double const offset, double const theta0, GaussianWalker &walker, const int n);

// mean of the flux of the fpt to inner disk
double
kac_flux_eccentric_inner_disk_outer_reflecting(const double R_int,const double R_out, double const offset,  GaussianWalker &walker, const int angle_subdivision, const int n);

// distribution of arrival times in offsetted inner target, with reflecting outer target.
py::list
fpt_distribution_eccentric_inner_disk_outer_reflecting_any_position(const double R_int,const double R_out, double const offset, double const r0,double const theta0, GaussianWalker &walker, const int n);
//
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


// distribution of convex hulls up to some number of steps
py::list
cvx_hull_distribution_free_space(GaussianWalker &walker, const int nbsteps, const int nbsimus);

// mean convex hulls up to some number of steps
double
mean_cvx_hull_free_space(GaussianWalker &walker, const int nbsteps, const int nbsimus);

// distribution of convex hulls up to escaping a disk of radius R
py::list
cvx_hull_distribution_before_FPT_to_rim(const double R, const double r0, GaussianWalker &walker, const int nbsimus);

// mean convex hulls up to escaping a disk of radius R
double
mean_cvx_hull_before_FPT_to_rim(const double R, const double r0, GaussianWalker &walker, const int nbsimus);

// distribution of convex hulls up to entering an inner target in a confining disk
py::list
cvx_hull_distribution_before_FPT_to_inner_target(const double rint, const double zint,  const double R, const double r0, const double theta0, GaussianWalker &walker, const int nbsimus);


// distribution of convex hulls up to entering an inner target in a confining disk
double
mean_cvx_hull_before_FPT_to_inner_target(const double rint, const double zint,  const double R, const double r0, const double theta0, GaussianWalker &walker, const int nbsimus);
