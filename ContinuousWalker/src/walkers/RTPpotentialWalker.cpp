#include <cmath>
#include <gsl/gsl_randist.h>
#include <gsl/gsl_rng.h>
#include <iostream>
#include <math.h>
#include <pybind11/pybind11.h>
#include <stdlib.h>
#include <string>

#include "ContinuousWalker.h"
// le include precedent est il necessaire?
#include "RTPpotentialWalker.h"

using namespace std;
namespace py = pybind11;

// uselul position increment functions for various potentials
// those take 4 parameters : (direction,fligh_time,position, speed, parameter)

// linear potential V(x) = a*x
double linear_potential(int direction, double flight_time, double position,
                        double speed, double param) {
  return (direction * speed - param) * flight_time;
}

// quadratic potential V(x) = a*x^2/2
double quadratic_potential(int direction, double flight_time, double position,
                           double speed, double param) {

  return (direction * speed - param * position) / param *
         (1 - exp(-param * flight_time));
}

RTPpotentialWalker::RTPpotentialWalker()
    : ContinuousWalker(), m_v(1.0), m_g(1.0) {
  m_potential_name = "linear";
  m_potential_parameter = 1.0;
  m_potential = &linear_potential;
}

RTPpotentialWalker::RTPpotentialWalker(double v, double g)
    : ContinuousWalker(), m_v(v), m_g(g) {
  m_potential_name = "linear";
  m_potential_parameter = 1.0;
  m_potential = &linear_potential;
}

RTPpotentialWalker::RTPpotentialWalker(std::string potential_name,
                                       double potential_paramer, double v,
                                       double g)
    : ContinuousWalker(), m_v(v), m_g(g), m_potential_name(potential_name),
      m_potential_parameter(potential_paramer) {
  if (m_potential_name == "linear") {
    m_potential = &linear_potential;

  } else if (m_potential_name == "quadratic") {
    m_potential = &quadratic_potential;
  } else {
    cout << "ERROR in init, allowed init is linear, quadratic" << endl;
    m_potential = &linear_potential;
  }
}

// bunch of getter setters
void RTPpotentialWalker::print_details() const {
  ContinuousWalker::print_details();
  cout << "speed param : " << m_v << endl;
  cout << "time scale param : " << m_g << endl;
  cout << "potential param : " << m_potential_parameter << endl;
  cout << "potential name : " << m_potential_name << endl;
}

double RTPpotentialWalker::get_v() const { return m_v; }
double RTPpotentialWalker::get_g() const { return m_g; }
double RTPpotentialWalker::get_potential_parameter() const {
  return m_potential_parameter;
}
void RTPpotentialWalker::get_potential() const {
  cout << "potential name : " << m_potential_name << endl;
}

void RTPpotentialWalker::set_v(double v) { m_v = v; }
void RTPpotentialWalker::set_g(double g) { m_g = g; }
void RTPpotentialWalker::set_potential_parameter(double potential_paramer) {
  m_potential_parameter = potential_paramer;
}

void RTPpotentialWalker::set_potential(std::string potential_name) {
  if (m_potential_name == "linear") {
    m_potential = &linear_potential;

  } else if (m_potential_name == "quadratic") {
    m_potential = &quadratic_potential;
  } else {
    cout << "ERROR in init, allowed init is linear, quadratic" << endl;
    m_potential = &linear_potential;
  }
}

// this is the classical virtual move function.
void RTPpotentialWalker::move(int verbose) {
  // compute flight time
  double flight_time = gsl_ran_exponential(m_rng, 1 / m_g);
  int direction = (int)(2 * gsl_ran_bernoulli(m_rng, 0.5) - 1);
  // cout << direction << endl;
  m_pos +=
      m_potential(direction, flight_time, m_pos, m_v, m_potential_parameter);
  m_lifetime += 1;
  if (verbose)
    cout << "pos : " << m_pos << endl;
  if (m_pos > m_max) {
    m_max = m_pos;
  } else if (m_pos < m_min) {
    m_min = m_pos;
  }
}

// PYBIND11_MODULE(module_ContinuousWalker,handle){
//    py::class_<RTPpotentialWalker,ContinuousWalker>(
//            handle, "RTPpotentialWalker"
//            )
//        .def(py::init<>())
//        .def(py::init<double,double>())
//        .def(py::init<string,double,int,double,double>())
//        .def("move",
//                &RTPpotentialWalker::move,"a function that makes the walker
//                perform a single step",py::arg("verbose")=0)
//        ;
//}
