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

// no potential
double no_potential(int direction, double flight_time, double position,
                    double speed, double param) {
  return (direction * speed) * flight_time;
}
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

// log potential V(x) = a*log(1+x) --> Not invertible (requires to solve
// w=e^x*x)
double log_potential(int direction, double flight_time, double position,
                     double speed, double param) {
  return 0;
}

// lifetime generators

double exponential_lifetime(gsl_rng *r, double rate) {
  return gsl_ran_exponential(r, 1 / rate);
}

// pareto distribution trucated before 1 (our arbitray choice here)
double pareto_lifetime(gsl_rng *r, double exponent) {
  return gsl_ran_pareto(r, exponent, 1.0);
}

// gamma distribution from GSL, with b=1 and a=exponent.
double gamma_lifetime(gsl_rng *r, double exponent) {
  return gsl_ran_gamma(r, exponent, 1.0);
}

RTPpotentialWalker::RTPpotentialWalker(std::string potential_name,
                                       double potential_paramer,
                                       std::string lifetime_name,
                                       double lifetime_parameter, double speed)
    : ContinuousWalker(), m_v(speed), m_potential_name(potential_name),
      m_potential_parameter(potential_paramer), m_lifetime_name(lifetime_name),
      m_lifetime_parameter(lifetime_parameter) {

  // implement logic of potential.
  if (m_potential_name == "linear") {
    m_potential = &linear_potential;
  } else if (m_potential_name == "quadratic") {
    m_potential = &quadratic_potential;
  } else if (m_potential_name == "log") {
    m_potential = &log_potential;
  } else {
    cout << "ERROR in init, allowed init is linear, quadratic, no potential "
            "chosen"
         << endl;
    m_potential = &no_potential;
    m_potential_name = "no potential";
  }
  // implement lifetime generator logic
  if (m_lifetime_name == "exponential") {
    m_lifetime_generator = &exponential_lifetime;
  } else if (m_lifetime_name == "pareto") {
    m_lifetime_generator = &pareto_lifetime;
  } else if (m_lifetime_name == "gamma") {
    m_lifetime_generator = &gamma_lifetime;
  } else {
    cout << "ERROR in init, allowed lifetime is exponential, gamma, pareto, "
            "exponential is default"
         << endl;
    m_lifetime_name = "exponential";
    m_lifetime_generator = &exponential_lifetime;
  }
}

// bunch of getter setters
void RTPpotentialWalker::print_details() const {
  ContinuousWalker::print_details();
  cout << "speed param : " << m_v << endl;
  cout << "potential name : " << m_potential_name << endl;
  cout << "potential param : " << m_potential_parameter << endl;
  cout << "lifetime generator name : " << m_lifetime_name << endl;
  cout << "lifetime generator param : " << m_lifetime_parameter << endl;
}

double RTPpotentialWalker::get_v() const { return m_v; }
double RTPpotentialWalker::get_potential_parameter() const {
  return m_potential_parameter;
}
void RTPpotentialWalker::get_potential() const {
  cout << "potential name : " << m_potential_name << endl;
}

double RTPpotentialWalker::get_lifetime_parameter() const {
  return m_lifetime_parameter;
}
void RTPpotentialWalker::get_lifetime_generator() const {
  cout << "lifetime genrator name : " << m_lifetime_name << endl;
}

void RTPpotentialWalker::set_v(double v) { m_v = v; }
void RTPpotentialWalker::set_potential_parameter(double potential_paramer) {
  m_potential_parameter = potential_paramer;
}

void RTPpotentialWalker::set_potential(std::string potential_name) {
  if (m_potential_name == "linear") {
    m_potential = &linear_potential;

  } else if (m_potential_name == "quadratic") {
    m_potential = &quadratic_potential;
  } else if (m_potential_name == "log") {
    m_potential = &log_potential;
  } else {
    cout << "ERROR in init, allowed init is linear, quadratic, no potential "
            "chosen"
         << endl;
    m_potential = &no_potential;
    m_potential_name = "no potential";
  }
}

void RTPpotentialWalker::set_lifetime_parameter(double lifetime_parameter) {
  m_lifetime_parameter = lifetime_parameter;
}

void RTPpotentialWalker::set_lifetime_generator(std::string lifetime_name) {
  if (m_lifetime_name == "exponential") {
    m_lifetime_generator = &exponential_lifetime;
  } else if (m_lifetime_name == "pareto") {
    m_lifetime_generator = &pareto_lifetime;
  } else if (m_lifetime_name == "gamma") {
    m_lifetime_generator = &gamma_lifetime;
  } else {
    cout << "ERROR in init, allowed lifetime is exponential, gamma, pareto, "
            "exponential is default"
         << endl;
    m_lifetime_name = "exponential";
    m_lifetime_generator = &exponential_lifetime;
  }
}
// this is the classical virtual move function.
void RTPpotentialWalker::move(int verbose) {
  // compute flight time
  double flight_time = m_lifetime_generator(m_rng, m_lifetime_parameter);
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
