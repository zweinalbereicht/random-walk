#include <iostream>
#include <vector>
#include <unordered_set>
#include <set>
#include <string>
#include <random>
#include <math.h>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>
#include <stdlib.h>

//useful shorthands
#define LOG(x) cout << x << endl
#define MOD(x,b) (x % b + b ) % b

#include "GaussianWalker.h"
using namespace std;


//default is a 2_dimensional walker starting from the origin, seeded at 1
GaussianWalker::GaussianWalker(): m_name("a simple isotropic gaussian walker"), m_pos(0.0,0.0), m_direction(0.0,0.0),m_max(0.0), m_lifetime(0.0), m_seed(1),m_d(2)
{
    for(int i=0;i<2;i++){
        m_direction.push_back(0.0); 
        m_pos.push_back(0.0); 
    }
    m_rng = gsl_rng_alloc(gsl_rng_mt19937); //on prend le mersenne un peu par default
    gsl_rng_set(m_rng,m_seed);
}

GaussianWalker::GaussianWalker(string name,int d, const pybind11::list &pos,int seed): m_name(name),m_seed(seed),m_lifetime(0.0),m_d(d)
{
    //on essaye tant bien que mal d'extraire cette merde
    for(int i=0;i<d;i++)
        m_pos.push_back(pos[i].cast<double>()); //attention ici on cast en double
    for(int i=0;i<d;i++)
        m_direction.push_back(0.0); //initialement la direction vaut 0 (pas de direction privilégiée)
    m_max=euclidian_distance(m_pos);
    m_rng = gsl_rng_alloc(gsl_rng_mt19937);
    gsl_rng_set(m_rng,seed);
}

GaussianWalker::~GaussianWalker()
{
    gsl_rng_free(m_rng);
}

void
GaussianWalker::print_details() const
{
    cout << "name : " << m_name << endl;
    cout << "dimension : " << m_d << endl;
    cout << "coordinates : ( ";
    for(int i=0;i<m_d;i++)
        cout << m_pos[i] << " ";
    cout << ")" <<endl;
    cout << "maximum : " << m_max << endl;
    cout << "lifetime : " << m_lifetime << endl;
    cout << "seed : " << m_seed << endl;
}

//getters

vector<double>
GaussianWalker::get_pos() const {
    return m_pos;
}

vector<double>
GaussianWalker::get_direction() const {
    return m_direction;
}

double GaussianWalker::get_max() const {
    return m_max;
}

double GaussianWalker::get_lifetime() const {
    return m_lifetime;
}

int GaussianWalker::get_seed() const {
    return m_seed;
}

//setters
void GaussianWalker::set_pos(const pybind11::list &pos){
    for(int i=0;i<m_pos.size();i++)
        m_pos[i]=pos[i].cast<double>();
}

void GaussianWalker::set_direction(const pybind11::list &direction){
    for(int i=0;i<m_direction.size();i++)
        m_pos[i]=direction[i].cast<double>();
}

void GaussianWalker::set_random_pos(const pybind11::list &dimensions){
    for(int i=0;i<m_pos.size();i++)
        m_pos[i]=dimensions[i].cast<double>()*gsl_rng_uniform(m_rng); //uniform initial position in a box
}

void  GaussianWalker::set_max(double max){
    m_max=max;
}


void  GaussianWalker::set_lifetime(double lifetime){
    m_lifetime=lifetime;
}

void  GaussianWalker::set_seed(int seed){
    m_seed=seed;
    gsl_rng_set(m_rng,m_seed);
}

//the basic move function
void
GaussianWalker::move(int verbose)
{
    // start by updating the direction on the unit sphere
    sphere_direction(m_d,m_direction,m_rng);
    // draw a random length
    double jump_length=gsl_ran_gaussian(m_rng,1.0); //just doing a gaussian step here for now
    //update all coordinates
    for(int i=0;i<m_d;i++){
        m_pos[i]+=jump_length*m_direction[i]; // move according to the jump drawn
    }
    m_lifetime+=1; //for now, in the case of instantaneous jumps
    double dist=euclidian_distance(m_pos);

    if(dist>m_max){
        m_max=dist;
    }

    if(verbose==1){
        cout << "coordinates : ( " ;
        for(int i=0;i<m_d;i++)
            cout << m_pos[i] << " ";
        cout << ")" <<endl;
    }
}

void
GaussianWalker::move_bounded(const pybind11::list &dimensions,int verbose)
{
    // start by updating the direction on the unit sphere
    sphere_direction(m_d,m_direction,m_rng);
    // draw a random length
    double jump_length=gsl_ran_gaussian(m_rng,1.0); //just doing a gaussian step here for now
    //update all coordinates
    for(int i=0;i<m_d;i++){
        m_pos[i]+=fmod(jump_length*m_direction[i],dimensions[i].cast<double>()); // move according to the jump drawn
    }
    m_lifetime+=1; //for now, in the case of instantaneous jumps
    double dist=euclidian_distance(m_pos);

    if(dist>m_max){
        m_max=dist;
    }

    if(verbose==1){
        cout << "coordinates : ( " ;
        for(int i=0;i<m_d;i++)
            cout << m_pos[i] << " ";
        cout << ")" <<endl;
    }
}

//other funtions 
//these move til death are gonna lead to infinite buckles, we will need to change them
void
GaussianWalker::move_til_death(int verbose)
{
    while(isAlive()){
        move(verbose);
    }
}

void
GaussianWalker::move_til_death_bounded(const pybind11::list &dimensions, int verbose) //the dimensions give the size of the hypercube we are moving in
{
    while(isAlive()){
        move_bounded(dimensions,verbose);
    }
}


bool GaussianWalker::isAlive() const
{
    return (euclidian_distance(m_pos)>=0); //For now this function is not working
}

void GaussianWalker::move_fixed_time(long time) // performs a certain number of steps --> the true time evolution is different
{
    for(long k=0;k<time;k++)
        move();
}

//useful functions 
double
euclidian_distance(const std::vector<double> &a,const std::vector<double> &b)
{
    double result;
    for(int i=0;i< a.size();i++)
        result+=pow(a[i]-b[i],2);
    return sqrt(result);
}

double
euclidian_distance(const std::vector<double> &a)
{
    double result;
    for(int i=0;i< a.size();i++){
        result+=pow(a[i],2);
    }
    return sqrt(result);
}

//takes a point on the unit sphere
void
sphere_direction(const int d, std::vector<double> &dir, gsl_rng* rng)
{
    double S=0.0;
    for(int i=0;i<d;i++){
        double x=gsl_ran_gaussian(rng,1.0/((double)sqrt(d)));
        dir[i]=x;
        S+=pow(x,2);
    }
    for(int i=0;i<d;i++){
        dir[i]=dir[i]/((double) sqrt(S));
    }
}
