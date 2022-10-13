#include <gsl/gsl_randist.h>
#include <gsl/gsl_rng.h>
#include <iostream>
#include <map>
#include <math.h>
#include <random>
#include <set>
#include <stdlib.h>
#include <string>
#include <unordered_set>
#include <vector>

// useful shorthands
#define LOG(x) cout << x << endl
#define MOD(x, b) (x % b + b) % b

#include "DiscreteWalker.h"
using namespace std;

// default is a 2_dimensional walker
DiscreteWalker::DiscreteWalker()
    : m_name("a simple 2 dimensional walker"), m_pos(2, 0), m_max(0),
      m_lifetime(0), m_seed(1), m_d(2) {
  m_max = 0.0;
  m_rng = gsl_rng_alloc(gsl_rng_mt19937);
  gsl_rng_set(m_rng, m_seed);
}

DiscreteWalker::DiscreteWalker(string name, int d, const pybind11::list &pos,
                               int seed)
    : m_name(name), m_seed(seed), m_lifetime(0), m_d(d) {
  // on essaye tant bien que mal d'extraire cette merde
  for (int i = 0; i < d; i++)
    m_pos.push_back(pos[i].cast<long>());
  m_max = euclidian_distance(m_pos);
  m_rng = gsl_rng_alloc(gsl_rng_mt19937);
  gsl_rng_set(m_rng, seed);
}

DiscreteWalker::~DiscreteWalker() { gsl_rng_free(m_rng); }

void DiscreteWalker::print_details() const {
  cout << "name : " << m_name << endl;
  cout << "dimension : " << m_d << endl;
  cout << "coordinates : ( ";
  for (int i = 0; i < m_d; i++)
    cout << m_pos[i] << " ";
  cout << ")" << endl;
  cout << "maximum : " << m_max << endl;
  cout << "age : " << m_lifetime << endl;
  cout << "seed : " << m_seed << endl;
}

// getters

pybind11::list DiscreteWalker::get_pos() const { return pybind11::cast(m_pos); }

long DiscreteWalker::get_max() const { return m_max; }

long DiscreteWalker::get_lifetime() const { return m_lifetime; }

int DiscreteWalker::get_seed() const { return m_seed; }

// setters
void DiscreteWalker::set_pos(const pybind11::list &pos) {
  for (int i = 0; i < m_pos.size(); i++)
    m_pos[i] = pos[i].cast<long>();

  double dis = euclidian_distance(m_pos);

  if (dis > m_max) {
    m_max = dis;
  }
}

void DiscreteWalker::set_random_pos(const pybind11::list &dimensions) {
  for (int i = 0; i < m_pos.size(); i++)
    m_pos[i] = gsl_rng_uniform_int(m_rng, dimensions[i].cast<long>());
}

/*
void DiscreteWalker::set_random_pos(long N){
     m_pos=1+gsl_rng_uniform_int(m_rng,N-1);
}
*/
void DiscreteWalker::set_max(double max) { m_max = max; }

void DiscreteWalker::set_lifetime(long lifetime) { m_lifetime = lifetime; }

void DiscreteWalker::set_seed(long seed) {
  m_seed = seed;
  gsl_rng_set(m_rng, m_seed);
}

// the basic move function
void DiscreteWalker::move(int verbose) {
  int coord =
      gsl_rng_uniform_int(m_rng, m_d); // choose which direction we gonna move
  int m = gsl_ran_bernoulli(
      m_rng, 0.5); // the basic move is +1 or -1 with equal probability
  m_pos[coord] += 1 - 2 * m;
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

void DiscreteWalker::move_bounded(const pybind11::list &dimensions,
                                  int verbose) {
  int coord =
      gsl_rng_uniform_int(m_rng, m_d); // choose which direction we gonna move
  int m = gsl_ran_bernoulli(
      m_rng, 0.5); // the basic move is +1 or -1 with equal probability
  m_pos[coord] =
      MOD(m_pos[coord] + (1 - 2 * m),
          dimensions[coord].cast<long>()); // ici on ajoute la periodicité
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

// this function is essentially the same as above but we are looking for speed
// iprovement here and want to bypass the cast part. Polymorphism should apply
// straighforwardly here
void DiscreteWalker::move_bounded(const vector<long> &dimensions, int verbose) {
  int coord =
      gsl_rng_uniform_int(m_rng, m_d); // choose which direction we gonna move
  int m = gsl_ran_bernoulli(
      m_rng, 0.5); // the basic move is +1 or -1 with equal probability
  m_pos[coord] = MOD(m_pos[coord] + (1 - 2 * m),
                     dimensions[coord]); // ici on ajoute la periodicité
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

// other funtions
void DiscreteWalker::move_til_death(int verbose) {
  while (isAlive()) {
    move(verbose);
  }
}

/*
//other funtions
//move til death with time threashold, to ensure that simulations in infinite
spaces terminate void DiscreteWalker::move_til_death(int verbose, const int
max_time){ while(isAlive() && m_lifetime < max_time){ move(verbose);
    }
}
*/

void DiscreteWalker::move_til_death_bounded(
    const pybind11::list &dimensions,
    int verbose) // the dimensions give the size of the hypercube we are moving
                 // in
{
  // fill the C++ vector
  vector<long> tmp;
  for (int i = 0; i < m_d; i++)
    tmp.push_back(dimensions[i].cast<long>());

  while (isAlive()) {
    move_bounded(tmp, verbose);
  }
}

long DiscreteWalker::move_til_death_bounded_record_territory(
    const pybind11::list &dimensions, int verbose) {
  // once again substitute list to vector

  vector<long> tmp;
  for (int i = 0; i < m_d; i++) {
    tmp.push_back(dimensions[i].cast<long>());
  }

  // we use sets which are built in hash tables. We would prefer unordered_set
  // but seems like the hash is harder to put in place so let's stick with that
  // for now.
  set<vector<long>> territory;

  territory.insert(m_pos); // put the first position
  while (isAlive()) {
    move_bounded(tmp, verbose);
    territory.insert(m_pos); /// put it in the set, should be average constant
                             /// time, doesn't do anything if already exists
  }

  return (long)territory.size();
}

long DiscreteWalker::move_til_death_fixed_time_record_territory(
    const int max_time, const int verbose) {
  // we use sets which are built in hash tables. We would prefer unordered_set
  // but seems like the hash is harder to put in place so let's stick with that
  // for now.
  set<vector<long>> territory;

  territory.insert(m_pos); // put the first position
  while (isAlive() && m_lifetime < max_time) {
    move(verbose);
    territory.insert(m_pos); /// put it in the set, should be average constant
                             /// time, doesn't do anything if already exists
  }

  // chexk how we terminated
  if (isAlive()) {
    return 0.0;
  }
  return (long)territory.size();
}

long DiscreteWalker::move_til_death_fixed_time(const int max_time,
                                               const int verbose) {

  while (isAlive() && m_lifetime < max_time) {
    move(verbose);
  }

  // chexk how we terminated
  if (isAlive()) {
    return 0.0;
  }
  return (long)m_lifetime;
}

bool DiscreteWalker::isAlive() const {
  return (euclidian_distance(m_pos) >=
          1); // strict inequality here and should take care of rounding errors
}

/*
int DiscreteWalker::move_fixed_max(long borne)
{
    while(isAlive() && m_pos<=borne){
        move();
    }
    if (!isAlive() && m_max==borne){
        return 0; //if success
    }
    else{
        return 1;
    }
}
*/

int DiscreteWalker::move_fixed_time(long time) {

  while (isAlive() && m_lifetime <= time) {
    move();
  }
  if (!isAlive() && m_lifetime == time) {
    return 0; // if success
  } else {
    return 1;
  }
}

long DiscreteWalker::move_til_fully_covered(const pybind11::list &dimensions,
                                            int max_time, int verbose) {
  // once again substitute list to vector

  vector<long> tmp;
  long territory_size = 1;
  for (int i = 0; i < m_d; i++) {
    tmp.push_back(dimensions[i].cast<long>());
    territory_size = territory_size * dimensions[i].cast<long>();
  }

  // we use sets which are built in hash tables. We would prefer unordered_set
  // but seems like the hash is harder to put in place so let's stick with that
  // for now.
  set<vector<long>> territory;

  territory.insert(m_pos); // put the first position
  while (territory.size() < territory_size && m_lifetime < max_time) {
    move_bounded(tmp, verbose);
    territory.insert(m_pos); /// put it in the set, should be average constant
                             /// time, doesn't do anything if already exists
  }

  if (m_lifetime < max_time) {
    return m_lifetime;
  } else {
    return 0;
  }
}

vector<long> DiscreteWalker::move_til_fully_covered_record_discovery_times(
    const pybind11::list &dimensions, int verbose) {
  // once again substitute list to vector

  vector<long> tmp;
  long territory_size = 1;
  for (int i = 0; i < m_d; i++) {
    tmp.push_back(dimensions[i].cast<long>());
    territory_size = territory_size * dimensions[i].cast<long>();
  }

  // we use sets which are built in hash tables. We would prefer unordered_set
  // but seems like the hash is harder to put in place so let's stick with that
  // for now.
  // We store the visited sites in a map
  map<vector<long>, long> territory;

  territory.insert(make_pair(m_pos, m_lifetime)); // put the first position
  while (territory.size() < territory_size) {
    move_bounded(tmp, verbose);
    territory.insert(make_pair(
        m_pos, m_lifetime)); /// put it in the map, should be average constant
                             /// time, doesn't do anything if already exists
  }

  vector<long> territory_as_vec;
  for (map<vector<long>, long>::iterator it = territory.begin();
       it != territory.end(); ++it) {
    territory_as_vec.push_back(it->second);
  }

  // std::cout << "We reached this inside point!" << std::endl;

  return territory_as_vec;
}

/*
double DiscreteWalker::split_prob(long s0, long s1,long s2, long const n)
{
    long i;
    //int result[n];
    vector<int> result(n); //encore une autre version, ne pas oublier le
#include <vector> en haut sinon ça ne marche pas.
    //result=(int*) malloc(sizeof(int)*n); old C version
    for(i=0;i<n;i++){
        m_lifetime=0;
        m_pos=s0;
        m_max=m_pos;
        m_min=m_pos;
        while(m_pos>s1 && m_pos<s2){ //attention aux inegalités ici, c'est
strict, on s'arrete lorsque l'on touche move(0);
        }
        result[i]=(int)(m_pos>=s2); //same thing here, watch the strictness
    }
    double m=0;
    for(i=0;i<n;i++){
        m+=result[i];
    }
    //cout << m << endl;
    //free(result); old C version, using fixed size declaration in the above
    return (double)(m/n);
}

double DiscreteWalker::max_prob(long s0, long s1,long const n)
{
    long i;
    //int result[n];
    vector<int> result(n); //encore une autre version, ne pas oublier le
#include <vector> en haut sinon ça ne marche pas.
    //result=(int*) malloc(sizeof(int)*n); old C version
    for(i=0;i<n;i++){
        m_lifetime=0;
        m_pos=s0;
        m_max=m_pos;
        m_min=m_pos;
        while(m_pos>0 && m_pos<=s1){ //attention aux inegalités ici, c'est
strict, on s'arrete lorsque l'on touche 0 ou que l'on depasse strictement s1
            move(0);
        }
        result[i]=(int)(m_max==s1); //same thing here, watch the strictness
    }
    double m=0;
    for(i=0;i<n;i++){
        m+=result[i];
    }
    //cout << m << endl;
    //free(result); old C version, using fixed size declaration in the above
    return (double)(m/n);
}
*/

double euclidian_distance(const std::vector<long> &a,
                          const std::vector<long> &b) {
  double result = 0;
  for (int i = 0; i < a.size(); i++)
    result += pow(a[i] - b[i], 2);
  return sqrt(result);
}

double euclidian_distance(const std::vector<long> &a) {
  double result = 0;
  for (int i = 0; i < a.size(); i++)
    result += pow(a[i], 2);
  return sqrt(result);
}
