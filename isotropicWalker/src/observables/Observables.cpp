#include <gsl/gsl_rng.h>
#include <iostream>
#include <pybind11/iostream.h>
#include <pybind11/numpy.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <stdlib.h>
#include <string>
#include <vector>

#include "../walkers/GaussianWalker.h"

#include "Observables.h"

#define LOG(x) cout << x << endl;

// this is a constant to make sure our program terminates because we have
// infinite mean return time. 1 billion might actually be big.
#define MAX_SIMU_STEPS 1000000000

using namespace std;
namespace py = pybind11;

double split_prob_hyperplane(const double x0, const double x,
                             GaussianWalker &walker, const int n) {
  vector<int> result_tmp(n);
  double run = 0;
  for (int i = 0; i < n; i++) {
    // prepare for the run
    walker.set_lifetime(0);
    walker.set_coord(0, x0);
    int d = walker.get_dimension();
    for (int k = 1; k < d; k++)
      walker.set_coord(k, 0.0);

    // run
    while (walker.get_pos()[0] >= 0 && walker.get_pos()[0] <= x) {
      walker.move();
    }
    run += (walker.get_pos()[0] > 0);
  }
  return (run / ((double)n));
}

// the walker starts on the x axis, at distance x0 from the origin
double split_prob_cone(const double r0, const double theta0, const double theta,
                       GaussianWalker &walker, const int n) {
  vector<int> result_tmp(n);
  double run = 0;
  for (int i = 0; i < n; i++) {
    // prepare for the run
    walker.set_lifetime(0);
    walker.set_coord(0, r0 * cos(theta0));
    walker.set_coord(1, r0 * sin(theta0));
    int d = walker.get_dimension();
    for (int k = 2; k < d; k++)
      walker.set_coord(k, 0.0);

    // run
    while (walker.get_angle() >= 0 && walker.get_angle() <= theta) {
      walker.move();
    }
    double angle = walker.get_angle();
    // This is not exact, there are some cases where we are not able to say
    // which side the cone was exited from, but it should be decent enough
    run += (int)(not(angle > -M_PI + theta && angle < 0.0));
  }
  return (run / ((double)n));
}

py::list radial_distance_when_crossing_hyperplan_distribution(
    const double x0, const double x, GaussianWalker &walker, const int n) {
  vector<float> distances(n);
  for (int i = 0; i < n; i++) {
    // prepare for the run
    walker.set_lifetime(0);
    walker.set_coord(0, x0);
    int d = walker.get_dimension();
    for (int k = 1; k < d; k++)
      walker.set_coord(k, 0.0);

    // run until we cross 0. Watch out as this can never terminate, we need to
    // input manually an upper bound on the number of steps to make sure out
    // program doesn't run for too long.
    while (walker.get_pos()[0] >= 0 && walker.get_lifetime() < MAX_SIMU_STEPS) {
      walker.move();
    }
    //
    // calculate the distance by projecting and then computing the
    // euclidian distance to 0, which is the projected distance of the
    // starting point.
    if (walker.get_lifetime() == MAX_SIMU_STEPS) {
      distances[i] = 0; // set to zero, shoudn't have much impact.
    } else {
      walker.set_coord(0, 0);
      distances[i] = euclidian_distance(walker.get_pos());
    }
  }
  py::list ret = py::cast(distances);
  return ret;
}
