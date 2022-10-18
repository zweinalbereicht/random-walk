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

ZipfWalker::ZipfWalker(double alpha) : DiscreteWalker(), m_alpha(alpha) {}

ZipfWalker::ZipfWalker(string name, long pos, int seed, double alpha)
    : DiscreteWalker(name, pos, seed), m_alpha(alpha) {}

void ZipfWalker::print_details() const {
  DiscreteWalker::print_details();
  cout << "alpha param : " << m_alpha << endl;
}

double ZipfWalker::get_alpha() const { return m_alpha; }

void ZipfWalker::set_alpha(double alpha) { m_alpha = alpha; }

void ZipfWalker::move(int verbose) {
  // double m = gsl_ran_levy(m_rng, m_c, m_alpha);

  unsigned int m = gsl_ran_zipf(m_rng, 1 + m_alpha);
  // cout << "abs val : " << m << endl;
  int dir = gsl_ran_bernoulli(m_rng, 0.5);
  // cout << "dir : " << dir << endl;
  m_pos = m_pos + ((long)(2 * dir - 1)) * ((long)m);

  // m_pos=round(m_pos+m);
  if (verbose)
    cout << "pos : " << m_pos << endl;
  // cout << "moving this move" << endl; //untick this if you want to make sure
  // the right function is called
  if (m_pos > m_max) {
    m_max = m_pos;
  } else if (m_pos < m_min) {
    m_min = m_pos;
  }
  m_lifetime += 1;
}
