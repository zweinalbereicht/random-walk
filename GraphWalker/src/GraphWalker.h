#pragma once

#include <iostream>
#include <random>
#include <string>
#include <vector>
#include <math.h>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>

//#include "../../pcg-cpp-0.98/include/pcg_test.h"
#include "../../Graphs/src/Graph.h"


//#include "../../custom_distributions/Zipf.h"




class GraphWalker
{

    //useful attributes for the walker
    protected:

    std::string m_name;
    int m_pos;
    long m_lifetime;
    int m_seed; //each walker will have it's own seed
    gsl_rng* m_rng; //and own random generator
    Graph m_graph;

    public:

    //constructeurs
    GraphWalker();
    GraphWalker(std::string filename, int pos,int seed);

    //destucteurs
    ~GraphWalker();

    //un printeur d'état
    virtual void print_details() const;

    //fonctions getters
    int get_pos() const ;
    long get_lifetime() const ;
    int get_seed() const ;

    //fonctions setters
    void set_pos(long pos);
    void set_lifetime(long lifetime);
    void set_seed(long seed);

    //other setter functions
    void set_random_pos(int N);

    void move(int verbose=0); //only virtual function a priori
    bool isAlive(int target) const;
    void move_til_death(int target, int verbose=0);
    int move_fixed_time(int target,long time);
    //double split_prob(long s0, long s1,long s2, long const n);

};

