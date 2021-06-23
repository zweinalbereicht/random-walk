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

int GraphWalker::get_graph_size() const {
    return m_graph.get_n();
}

//setters
void GraphWalker::set_pos(const int pos){
     m_pos=pos;
}

void GraphWalker::set_random_pos(){
     m_pos=gsl_rng_uniform_int(m_rng,m_graph.get_n());
}

void  GraphWalker::set_lifetime(const long lifetime){
    m_lifetime=lifetime;
}

void  GraphWalker::set_seed(const int seed){
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

void
GraphWalker::move_nsteps(int n,int verbose)
{
    for(int i=0;i<n;i++)
        move(verbose);
}

//other funtions
void
GraphWalker::move_til_death(const int target,int verbose){
    while(isAlive(target)){
        move(verbose);
    }
}

bool GraphWalker::isAlive(const int target) const
{
    return (m_pos!=target); //strict inequality here
}

int  GraphWalker::move_fixed_time(const int target,long time)
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

int
GraphWalker::move_til_death_record_territory(const int target,int verbose)
{
    vector<int> territory(m_graph.get_n()); //the territory on which we walk
    long i=0;
    for(;i<m_graph.get_n();i++)
        territory[i]=0;

    territory[m_pos]+=1; //setting the first position
    while(isAlive(target)){
        move(verbose);
        territory[m_pos]+=1;
    }

    int result=0; // parcourons le tableau de sortie
    for(i=0;i<m_graph.get_n();i++)
        if(territory[i]>0)
            result+=1;
    return result;
}

void
GraphWalker::move_til_death_territory_max_dist(const int target,vector<int> &tmp,const vector<int> &SP)
{
    //clear tmp
    tmp.clear();
    //size of graph
    int n=m_graph.get_n();
    vector<int> territory(m_graph.get_n()); //the territory on which we walk
    long i=0;
    int max_dist=SP[n*m_pos+target];
    for(;i<m_graph.get_n();i++)
        territory[i]=0;

    territory[m_pos]+=1; //setting the first position
    while(isAlive(target)){
        move();
        territory[m_pos]+=1;
        if(SP[n*m_pos+target]>max_dist)
            max_dist=SP[n*m_pos+target];
    }

    long result=0; // parcourons le tableau de sortie
    for(i=0;i<m_graph.get_n();i++)
        if(territory[i]>0)
            result+=1;
    tmp.push_back(result);
    tmp.push_back(max_dist);
}

