#include <gsl/gsl_randist.h>
#include <gsl/gsl_rng.h>
#include <iostream>
#include <math.h>
#include <pybind11/iostream.h>
#include <pybind11/numpy.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <stdlib.h>
#include <string>
#include <vector>

#include "../walkers/BiasedWalker.h"
#include "../walkers/DiscreteWalker.h"
#include "../walkers/RiemannWalker.h"
#include "../walkers/SATWWalker.h"

#include "Observables.h"

using namespace std;
namespace py = pybind11;

py::list fpt_arrival_bounded_distribution(const long s0, const long N,
                                          DiscreteWalker &walker, const int n) {
  vector<long> result(n);
  for (int i = 0; i < n; i++) {
    walker.set_lifetime(0);
    walker.set_pos(s0);
    walker.move_til_death_bounded(N);
    result[i] = walker.get_lifetime();
  }

  py::list ret = py::cast(result);
  return ret;
}

double fpt_arrival_bounded_global_mean(const long N, DiscreteWalker &walker,
                                       const int n) {
  vector<long> result(n);
  for (int i = 0; i < n; i++) {
    walker.set_lifetime(0);
    walker.set_random_pos(N);
    walker.move_til_death_bounded(N);
    result[i] = walker.get_lifetime();
  }

  double m;

  for (int i = 0; i < n; i++) {
    m += result[i];
  }

  return (double)m / n;
}

double fpt_arrival_bounded_mean(const long s0, const long N,
                                DiscreteWalker &walker, const int n) {
  vector<long> result(n);
  for (int i = 0; i < n; i++) {
    walker.set_lifetime(0);
    walker.set_pos(s0);
    walker.move_til_death_bounded(N);
    result[i] = walker.get_lifetime();
  }

  double m;

  for (int i = 0; i < n; i++) {
    m += result[i];
  }

  return (double)m / n;
}

py::list territory_distribution(const long s0, const long N,
                                DiscreteWalker &walker, const int n) {
  vector<long> result(n);
  for (int i = 0; i < n; i++) {
    walker.set_lifetime(0);
    walker.set_pos(s0);
    result[i] =
        walker.move_til_death_bounded_record_territory(N); // a implementer
  }

  py::list ret = py::cast(result);
  return ret;
}

py::list territory_distribution_fixed_time_infinite(const long s0,
                                                    DiscreteWalker &walker,
                                                    const int nb_steps,
                                                    const int nb_simus) {
  vector<long> result(nb_simus);
  for (int i = 0; i < nb_simus; i++) {
    walker.set_lifetime(0);
    walker.set_pos(s0);
    result[i] = walker.move_infinite_fixed_time_and_record_territory(
        nb_steps); // a implementer
  }

  py::list ret = py::cast(result);
  return ret;
}

py::list territory_distribution_infinite(const long s0, const long max_steps,
                                         DiscreteWalker &walker, const int n) {
  vector<long> result(n);
  for (int i = 0; i < n; i++) {
    walker.set_lifetime(0);
    walker.set_pos(s0);
    result[i] = walker.move_til_death_arrival_record_territory(
        max_steps); // a implementer
  }

  py::list ret = py::cast(result);
  return ret;
}

double territory_global_mean(const long N, DiscreteWalker &walker,
                             const int n) {
  vector<long> result(n);
  for (int i = 0; i < n; i++) {
    walker.set_lifetime(0);
    walker.set_random_pos(N);
    result[i] =
        walker.move_til_death_bounded_record_territory(N); // a implementer
  }

  double m;

  for (int i = 0; i < n; i++) {
    m += result[i];
  }

  return (double)m / n;
}

double territory_mean(const long s0, const long N, DiscreteWalker &walker,
                      const int n) {
  vector<long> result(n);
  for (int i = 0; i < n; i++) {
    walker.set_lifetime(0);
    walker.set_pos(s0);
    result[i] =
        walker.move_til_death_bounded_record_territory(N); // a implementer
  }

  double m;

  for (int i = 0; i < n; i++) {
    m += result[i];
  }

  return (double)m / n;
}

double rosenstock_fixed_time(const long s0, DiscreteWalker &walker,
                             const int time, const double rho, const int n,
                             const int verbose) {

  double m = 0.0;
  if (time < s0 ||
      (s0 + time) % 2 == 1) // il faut avoir le temps d'aller jusqu'à 0 quand
                            // même et que la parité fonctionne bien
    return 0.0;

  int success = 0;
  double survival_probability;
  while (success < n) {
    walker.set_lifetime(0); // attention a bien reinitialiser ici
    walker.set_pos(s0);
    walker.set_max(s0);

    for (int i = 0; i < time; i++) {
      walker.move(verbose);
    }
    if (walker.get_pos() == 0) {
      m = pow(1 - rho, walker.get_max());
      if (gsl_rng_uniform(walker.get_rng()) < m) {
        survival_probability++;
      }
      success++;
    }
  }
  if (m == 0)
    return 0.0;
  return survival_probability / ((double)n);
}

py::list conditional_fpt_distribution(const long s0, const long x,
                                      DiscreteWalker &walker, const long N,
                                      const bool target) {

  if (s0 <= 0 || s0 >= x) {
    exit(1);
  }

  vector<long> result(N);
  long nb_success = 0;

  while (nb_success < N) {
    walker.set_lifetime(0);
    walker.set_pos(s0);
    while (walker.get_pos() < x &&
           walker.get_pos() > 0) { // on bouge jusqu'à sortir de l'intervalle
      walker.move();
    }
    if (target == 0 && !walker.isAlive()) { // si on sort en zero, on doit
                                            // toucher zero exactement
      result[nb_success] = walker.get_lifetime();
      nb_success++;
    } else if (target == 1 && walker.isAlive()) { // si on sort en x
      result[nb_success] = walker.get_lifetime();
      nb_success++;
    }
  }

  py::list ret = py::cast(result);
  return ret;
}

// renvoie la moyenne du temps de passage conditionnel à travers
// target(0=0,1=x), entre x et 0
double conditional_fpt_mean(const double s0, const double x,
                            DiscreteWalker &walker, const long N,
                            const bool target) {

  if (s0 <= 0 || s0 >= x) {
    exit(1);
  }

  vector<long> result;
  long nb_success = 0;
  double mean = 0.0;

  while (nb_success <= N) {
    walker.set_lifetime(0);
    walker.set_pos(s0);
    while (walker.get_pos() < x &&
           walker.get_pos() > 0) { // on bouge jusqu'à sortir de l'intervalle,
                                   // en touchant exactement le bord
      walker.move();
    }
    if (target == 0 && !walker.isAlive()) { // si on sort en zero
      result.push_back(walker.get_lifetime());
      nb_success++;
    } else if (target == 1 && walker.isAlive()) { // si on sort en x
      result.push_back(walker.get_lifetime());
      nb_success++;
    }
  }

  for (auto el : result) {
    mean += el;
  }
  return mean / ((double)N);
}

py::list fpt_arrival_distribution(const long s0, const long max_steps,
                                  DiscreteWalker &walker, const int n) {
  vector<long> result(n);
  for (int i = 0; i < n; i++) {
    walker.set_lifetime(0);
    walker.set_pos(s0);
    result[i] = walker.move_til_death_arrival_max_steps(max_steps);
  }

  py::list ret = py::cast(result);
  return ret;
}

double survival_probability(const long s0, const long n, DiscreteWalker &walker,
                            const long N) {

  if (s0 == 0) { // in case we start from the absorbing site
    return 0.0;
  }

  double probability = 0.0;
  for (int i = 0; i < N; i++) {
    // attention à réinitialiser la position, le min le max et l'age sinon on a
    // des problemes avec les non markoviennes!
    walker.set_lifetime(0);
    walker.set_pos(s0);
    walker.set_max(s0);
    walker.set_min(s0);
    while (walker.isAlive() && walker.get_lifetime() < n) {
      walker.move();
    }
    probability += walker.isAlive();
  }
  return probability / ((double)N);
}

double splitting_probability(const long s0, const long x,
                             DiscreteWalker &walker, const long N) {

  if (s0 == 0) { // in case we start from the absorbing site on the left
    return 0.0;
  }
  if (s0 == x) { // in case we start from the absorbing site on the right
    return 1.0;
  }

  double probability = 0.0;

  for (int i = 0; i < N; i++) {
    // attention à réinitialiser la position, le min le max et l'age sinon on a
    // des problemes avec les non markoviennes!
    walker.set_lifetime(0);
    walker.set_pos(s0);
    walker.set_max(s0);
    walker.set_min(s0);
    long elapsed_time = 0;
    // on s'arrete lorqu'on touche exactement 0 ou x (on est dans un setup
    // discret ici)
    while (walker.get_pos() < x && walker.get_pos() > 0) {
      walker.move();
    }
    probability +=
        (walker.isAlive()); // c'est bien la split de toucher x avant 0 ici
  }
  return probability / ((double)N);
}

py::list map_of_explored_territory_distribution(const long s0, const long N,
                                                DiscreteWalker &walker,
                                                const long nb_steps,
                                                const long nb_simus) {

  vector<vector<long>> territories;
  for (int i = 0; i < nb_simus; i++) {
    walker.set_lifetime(0);
    walker.set_pos(s0);
    // here we use a method that not only returns the number of visited sites
    // but also which one were visited
    territories.push_back(
        walker.move_fixed_time_and_draw_map(N, nb_steps)); // a implementer
  }

  py::list ret = py::cast(territories);
  return ret;
}

py::list territory_discovery_time_distribution(const long s0, const long N,
                                               DiscreteWalker &walker,
                                               const long nb_steps,
                                               const long nb_simus) {

  vector<vector<long>> territories;
  for (int i = 0; i < nb_simus; i++) {
    walker.set_lifetime(0);
    walker.set_pos(s0);
    territories.push_back(
        walker.move_fixed_time_and_record_discovery_time(N, nb_steps));
  }

  py::list ret = py::cast(territories);
  return ret;
}

py::list discovery_times_before_cover_time_distribution(const long s0,
                                                        const long N,
                                                        DiscreteWalker &walker,
                                                        const long nb_simus) {

  vector<vector<long>> territories;
  for (int i = 0; i < nb_simus; i++) {
    walker.set_lifetime(0);
    walker.set_pos(s0);
    territories.push_back(walker.move_til_covered_record_discovery_time(N));
  }

  py::list ret = py::cast(territories);
  return ret;
}

py::list territory_infinite_discovery_time_distribution(const long s0,
                                                        DiscreteWalker &walker,
                                                        const long nb_steps,
                                                        const long nb_simus) {

  vector<vector<long>> territories;
  for (int i = 0; i < nb_simus; i++) {
    walker.set_lifetime(0);
    walker.set_pos(s0);
    territories.push_back(
        walker.move_infinite_fixed_time_and_record_discovery_time(nb_steps));
  }

  py::list ret = py::cast(territories);
  return ret;
}

double cover_time_mean(const long s0, const long size, DiscreteWalker &walker,
                       const int nb_simus) {

  vector<long> result(nb_simus);
  for (int i = 0; i < nb_simus; i++) {
    walker.set_lifetime(0);
    walker.set_pos(s0);
    result[i] = walker.move_til_covered(size);
  }

  //  sum to obtain the mean
  double m;
  for (int i = 0; i < nb_simus; i++) {
    m += result[i];
  }
  return (double)m / nb_simus;
}

py::list cover_time_fpt_ratio_distribution(const long s0,
                                           DiscreteWalker &walker,
                                           const long size,
                                           const long nb_simus) {
  vector<double> result(nb_simus);
  for (int i = 0; i < nb_simus; i++) {
    walker.set_lifetime(0);
    walker.set_pos(s0);
    result[i] = walker.move_til_covered_record_ratio(size);
  }

  py::list ret = py::cast(result);
  return ret;
}
