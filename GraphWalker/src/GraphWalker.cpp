#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <math.h>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>
#include <stdlib.h>

//#include "../../pcg-cpp-0.98/include/pcg_test.h"

#include "GraphWalker.h"

using namespace std;


GraphWalker::GraphWalker() : m_pos(0),m_lifetime(0),m_seed(1),m_graph(1){
    m_rng = gsl_rng_alloc(gsl_rng_mt19937);
    gsl_rng_set(m_rng,m_seed);
}

GraphWalker::GraphWalker(std::string filename, int pos,int seed) : m_pos(pos), m_seed(seed), m_lifetime(0),m_graph(filename)
{
    m_rng = gsl_rng_alloc(gsl_rng_mt19937);
    gsl_rng_set(m_rng,m_seed);
}

GraphWalker::~GraphWalker()
{
    gsl_rng_free(m_rng);
}

void
GraphWalker::print_details() const
{
    cout << "position : " << m_pos << endl;
    cout << "age : " << m_lifetime << endl;
    cout << "seed : " << m_seed << endl;

    //m_graph.show_matrix();
}

//getters
int GraphWalker::get_pos() const {
    return m_pos;
}

long GraphWalker::get_lifetime() const {
    return m_lifetime;
}

int GraphWalker::get_seed() const {
    return m_seed;
}

//setters
void GraphWalker::set_pos(long pos){
     m_pos=pos;
}

void GraphWalker::set_random_pos(int N){
     m_pos=1+gsl_rng_uniform_int(m_rng,N-1);
}

void  GraphWalker::set_lifetime(long lifetime){
    m_lifetime=lifetime;
}

void  GraphWalker::set_seed(long seed){
    m_seed=seed;
    gsl_rng_set(m_rng,m_seed);
}

//the basic move function
void
GraphWalker::move(int verbose){
    int nb_neighbors = m_graph.m_alist[m_pos].m_d;
    int m = gsl_rng_uniform_int(m_rng, nb_neighbors);
    //go to a random neighbor
    m_pos=m_graph.m_alist[(int) m_pos].m_list[m];
    if(verbose==1){
        cout << m_pos << " -> ";
        //cout << "position : " << m_pos << endl;
    }
    m_lifetime++;
}

//other funtions
void
GraphWalker::move_til_death(int target,int verbose){
    while(isAlive(target)){
        move(verbose);
    }
}

bool GraphWalker::isAlive(int target) const
{
    return (m_pos==target); //strict inequality here
}

int  GraphWalker::move_fixed_time(int target,long time)
{

    while(isAlive(target) && m_lifetime<=time){
        move();
    }
    if (!isAlive(target) && m_lifetime==time){
        return 0; //if success
    }
    else{
        return 1;
    }
}
