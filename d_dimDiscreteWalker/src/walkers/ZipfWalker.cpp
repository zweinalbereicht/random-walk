#include <gsl/gsl_randist.h>
#include <gsl/gsl_rng.h>
#include <iostream>
#include <math.h>
#include <pybind11/pybind11.h>
#include <stdlib.h>
#include <string>

#include "DiscreteWalker.h"
// le include precedent est il necessaire?
#include "ZipfWalker.h"

using namespace std;
namespace py = pybind11;

ZipfWalker::ZipfWalker() : DiscreteWalker(), m_alpha(2.0) {}

// this is in two D
ZipfWalker::ZipfWalker(double alpha) : DiscreteWalker(), m_alpha(alpha) {}

ZipfWalker::ZipfWalker(std::string name, int d, const pybind11::list &pos,
                       double alpha, int seed)
    : DiscreteWalker(name, d, pos, seed), m_alpha(alpha) {}

void ZipfWalker::print_details() const {
  DiscreteWalker::print_details();
  cout << "alpha param : " << m_alpha << endl;
}

double ZipfWalker::get_alpha() const { return m_alpha; }

void ZipfWalker::set_alpha(double alpha) { m_alpha = alpha; }

void ZipfWalker::move(int verbose) {

  int coord =
      gsl_rng_uniform_int(m_rng, m_d); // choose which direction we gonna move
  int dir = gsl_ran_bernoulli(
      m_rng, 0.5); // the basic move is +1 or -1 with equal probability
  unsigned int m = gsl_ran_zipf(m_rng, 1 + m_alpha);

  // make the move
  m_pos[coord] += ((long)(2 * dir - 1)) * ((long)m);
  m_lifetime += 1;
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
