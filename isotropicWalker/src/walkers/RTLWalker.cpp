#include <gsl/gsl_randist.h>
#include <gsl/gsl_rng.h>
#include <iostream>
#include <math.h>
#include <pybind11/pybind11.h>
#include <stdlib.h>
#include <string>

#include "GaussianWalker.h"
// le include precedent est il necessaire?
#include "RTLWalker.h"

using namespace std;
namespace py = pybind11;

RTLWalker::RTLWalker() : GaussianWalker(), m_v(1.0), m_g(1.0) {
  m_name = "A simple run and tumble particle";
}

RTLWalker::RTLWalker(double g, double v) : GaussianWalker(), m_g(g), m_v(v) {
  m_name = "A simple run and tumble particle";
}

RTLWalker::RTLWalker(string name, int dim, const pybind11::list &pos, int seed,
                     double g, double v)
    : GaussianWalker(name, dim, pos, seed), m_g(g), m_v(v) {
  m_name = "A simple run and tumble particle";
}

void RTLWalker::print_details() const {
  GaussianWalker::print_details();
  cout << "time scale param : " << m_g << endl;
  cout << "speed param : " << m_v << endl;
  cout << "WARNING : the time is counted countinuously for this guy!! it's "
          "lifetime evolves not by steps of one."
       << endl;
}

double RTLWalker::get_g() const { return m_g; }

double RTLWalker::get_v() const { return m_v; }

void RTLWalker::set_g(double g) { m_g = g; }

void RTLWalker::set_v(double v) { m_v = v; }

void RTLWalker::move(int verbose) {
  // start by updating the direction on the unit sphere
  sphere_direction(m_d, m_direction, m_rng);
  // draw a random length
  double jump_length =
      gsl_ran_exponential(m_rng, m_g); // we first draw the time of the run
  // update all coordinates
  for (int i = 0; i < m_d; i++) {
    m_pos[i] +=
        m_v * jump_length * m_direction[i]; // move according to the jump drawn,
                                            // so we multiply by the speed
  }
  m_lifetime += jump_length; // we count the time elapsed durung the run phase
  double dist = euclidian_distance(m_pos);

  if (dist > m_max) {
    m_max = dist;
  }

  if (verbose == 1) {
    cout << "coordinates : ( ";
    for (int i = 0; i < m_d; i++)
      cout << m_pos[i] << " ";
    cout << ")" << endl;
  }
}
