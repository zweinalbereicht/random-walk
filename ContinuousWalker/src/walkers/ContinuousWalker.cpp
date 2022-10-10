#include <gsl/gsl_randist.h>
#include <gsl/gsl_rng.h>
#include <iostream>
#include <math.h>
#include <set>
#include <stdlib.h>
#include <string>
#include <vector>

#include "ContinuousWalker.h"
#include "GammaWalker.h"
#include "LaplaceWalker.h"
#include "LevyWalker.h"

using namespace std;

double mod_double(double x, double y) {
  if (x > 0) {
    return fmod(x, y);
  } else {
    return fmod(y + fmod(x, y), y);
  }
}

ContinuousWalker::ContinuousWalker() {
  m_name = "a simple walker";
  m_pos = 1.0;
  m_max = m_pos;
  m_min = m_pos;
  m_lifetime = 0;
  m_seed = 1;
  m_rng = gsl_rng_alloc(gsl_rng_mt19937);
  gsl_rng_set(m_rng, m_seed);
}

ContinuousWalker::ContinuousWalker(string name, double pos, int seed)
    : m_name(name), m_pos(pos), m_max(pos), m_min(pos), m_seed(seed),
      m_lifetime(0) {
  m_rng = gsl_rng_alloc(gsl_rng_mt19937);
  gsl_rng_set(m_rng, seed);
}

ContinuousWalker::~ContinuousWalker() { gsl_rng_free(m_rng); }

void ContinuousWalker::print_details() const {
  cout << "name : " << m_name << endl;
  cout << "position : " << m_pos << endl;
  cout << "maximum : " << m_max << endl;
  cout << "minimum : " << m_min << endl;
  cout << "age : " << m_lifetime << endl;
  cout << "seed : " << m_seed << endl;
}

// getters
double ContinuousWalker::get_pos() const { return m_pos; }

double ContinuousWalker::get_max() const { return m_max; }

double ContinuousWalker::get_min() const { return m_min; }

long ContinuousWalker::get_lifetime() const { return m_lifetime; }

int ContinuousWalker::get_seed() const { return m_seed; }

// setters
void ContinuousWalker::set_pos(double pos) { m_pos = pos; }

void ContinuousWalker::set_max(double max) { m_max = max; }

void ContinuousWalker::set_min(double min) { m_min = min; }

void ContinuousWalker::set_lifetime(long lifetime) { m_lifetime = lifetime; }

void ContinuousWalker::set_seed(long seed) {
  m_seed = seed;
  gsl_rng_set(m_rng, m_seed);
}

// the basic move function
void ContinuousWalker::move(int verbose) {
  double m = gsl_ran_gaussian(m_rng, 1.0); // the basic move is a gaussian step
  m_pos = m_pos + ((double)m);
  m_lifetime += 1;
  if (m_pos > m_max) {
    m_max = m_pos;
  } else if (m_min > m_pos) {
    m_min = m_pos;
  }
  if (verbose == 1) {
    cout << "position : " << m_pos << endl;
  }
}
// the basic move function on a torus
void ContinuousWalker::move_bounded(double size, int verbose) {
  move(verbose);
  m_pos = mod_double(m_pos, size);
}

// the basic move function on a torus
void ContinuousWalker::move_bounded_fixed_time(double size, long time) {
  for (long i = 0; i < time; i++) {
    move_bounded(size);
  }
}

long ContinuousWalker::move_fixed_time_record_territory(long time) {
  set<long> territory;
  for (long i = 0; i < time; i++) {
    move();
    territory.insert(floor(m_pos));
  }
  return (long)territory.size();
}

long ContinuousWalker::move_til_covered(double size) {

  vector<long> territory((long)size, 0);
  territory[0] = 1;
  long unvisited_territory = (long)size - 1;
  while (unvisited_territory > 0) {
    move_bounded(size);
    if (territory[floor(m_pos)] == 0) {
      unvisited_territory -= 1;
      territory[floor(m_pos)] = 1;
    }
  }
  return m_lifetime;
}

// other funtions
void ContinuousWalker::move_til_death(int verbose) {
  while (isAlive()) {
    move(verbose);
  }
}

bool ContinuousWalker::isAlive()
    const { // cela nous permet de prendre la convention crossing en compte, de
            // toute manière on ne tombera jamais sur zero pile
  return (m_pos >= 0);
}

int ContinuousWalker::move_fixed_max(double borne) {
  while (isAlive() && m_pos <= borne) {
    move();
  }
  if (!isAlive() && m_max == borne) {
    return 0;
  }
  return 1;
}

void ContinuousWalker::move_fixed_time(long time) {
  for (long i = 0; i < time; i++) {
    move();
  }
}

double ContinuousWalker::split_prob(double s0, double s1, double s2,
                                    int const n) {
  int i;
  // int result[n];
  vector<int> result(n); // encore une autre version, ne pas oublier le #include
                         // <vector> en haut sinon ça ne marche pas.
  // result=(int*) malloc(sizeof(int)*n); old C version
  for (i = 0; i < n; i++) {
    m_lifetime = 0;
    m_pos = s0;
    m_max = m_pos;
    m_min = m_pos;
    while (m_pos >= s1 && m_pos <= s2) { // attentionn aux inegalités ici
      // cout << "in here" << endl;
      move(0);
    }
    result[i] = (int)(m_pos > s2);
  }
  double m = 0;
  for (i = 0; i < n; i++) {
    m += result[i];
  }
  // free(result); old C version, using fixed size declaration in the above
  return (double)(m / n);
}
