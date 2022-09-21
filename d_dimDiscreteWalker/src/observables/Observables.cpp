#include <gsl/gsl_rng.h>
#include <iostream>
#include <pybind11/iostream.h>
#include <pybind11/numpy.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <stdlib.h>
#include <string>
#include <vector>

#include "../walkers/DiscreteWalker.h"

#include "Observables.h"

#define LOG(x) cout << x << endl;

using namespace std;
namespace py = pybind11;

py::list fpt_arrival_bounded_distribution(const pybind11::list &s0,
                                          const pybind11::list &dimensions,
                                          DiscreteWalker &walker, const int n) {
  vector<long> result(n);
  for (int i = 0; i < n; i++) {
    walker.set_lifetime(0);
    walker.set_pos(s0);
    walker.move_til_death_bounded(dimensions);
    result[i] = walker.get_lifetime();
  }

  py::list ret = py::cast(result);
  return ret;
}

double fpt_arrival_bounded_global_mean(const pybind11::list &dimensions,
                                       DiscreteWalker &walker, const int n) {
  vector<long> result(n);
  for (int i = 0; i < n; i++) {
    walker.set_lifetime(0);
    walker.set_random_pos(dimensions);
    walker.move_til_death_bounded(dimensions);
    result[i] = walker.get_lifetime();
  }

  double m;

  for (int i = 0; i < n; i++) {
    m += result[i];
  }

  return (double)m / n;
}

double fpt_arrival_bounded_mean(const pybind11::list &s0,
                                const pybind11::list &dimensions,
                                DiscreteWalker &walker, const int n) {
  vector<long> result(n);
  for (int i = 0; i < n; i++) {
    walker.set_lifetime(0);
    walker.set_pos(s0);
    walker.move_til_death_bounded(dimensions);
    result[i] = walker.get_lifetime();
  }

  double m;

  for (int i = 0; i < n; i++) {
    m += result[i];
  }

  return (double)m / n;
}

py::list territory_distribution(const pybind11::list &s0,
                                const pybind11::list &dimensions,
                                DiscreteWalker &walker, const int n) {
  vector<long> result(n);
  for (int i = 0; i < n; i++) {
    walker.set_lifetime(0);
    walker.set_pos(s0);
    result[i] = walker.move_til_death_bounded_record_territory(
        dimensions); // a implementer
  }

  py::list ret = py::cast(result);
  return ret;
}

double territory_mean(const pybind11::list &s0,
                      const pybind11::list &dimensions, DiscreteWalker &walker,
                      const int n) {
  vector<long> result(n);
  for (int i = 0; i < n; i++) {
    walker.set_lifetime(0);
    walker.set_pos(s0);
    result[i] = walker.move_til_death_bounded_record_territory(dimensions);
  }

  double m;

  for (int i = 0; i < n; i++) {
    m += result[i];
  }

  return (double)m / n;
}

double territory_global_mean(const pybind11::list &dimensions,
                             DiscreteWalker &walker, const int n) {
  vector<long> result(n);
  for (int i = 0; i < n; i++) {
    walker.set_lifetime(0);
    walker.set_random_pos(dimensions);
    result[i] = walker.move_til_death_bounded_record_territory(
        dimensions); // a implementer
  }

  double m;

  for (int i = 0; i < n; i++) {
    m += result[i];
  }

  return (double)m / n;
}

py::list territory_unbounded_fixed_time_distribution(const pybind11::list &s0,
                                                     DiscreteWalker &walker,
                                                     const int max_time,
                                                     const int n) {
  vector<long> result_tmp(n);
  vector<long> result;
  for (int i = 0; i < n; i++) {
    walker.set_lifetime(0);
    walker.set_pos(s0);
    // set the verbosity to one here
    int verbose = 0;
    result_tmp[i] =
        walker.move_til_death_fixed_time_record_territory(max_time, verbose);
  }

  for (auto el : result_tmp) {
    if (el > 0) {
      // LOG(el);
      result.push_back(el);
    }
  }

  py::list ret = py::cast(result);
  return ret;
}

double territory_unbounded_fixed_time_mean(const pybind11::list &s0,
                                           DiscreteWalker &walker,
                                           const int max_time, const int n) {
  vector<long> result_tmp(n);
  vector<long> result_fin;
  // setting verbosity
  int verbose = 0;
  for (int i = 0; i < n; i++) {
    walker.set_lifetime(0);
    walker.set_pos(s0);
    result_tmp[i] =
        walker.move_til_death_fixed_time_record_territory(max_time, verbose);
  }
  for (auto el : result_tmp) {
    if (el > 0) {
      result_fin.push_back(el);
    }
  }

  double m = 0.0;

  for (int i = 0; i < result_fin.size(); i++) {
    m += (double)result_fin[i];
  }

  if (m == 0.0) {
    return 0.0;
  } else {
    return (double)m / ((double)result_fin.size());
  }
}
