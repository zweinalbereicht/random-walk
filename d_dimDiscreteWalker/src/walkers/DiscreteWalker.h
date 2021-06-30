#pragma once

#include <iostream>
#include <random>
#include <string>
#include <math.h>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>


class DiscreteWalker
{

    //useful attributes for the walker
    protected:

    std::string m_name;
    int m_d; //the dimension of the hypercube
    std::vector<long> m_pos;
    long m_lifetime;
    long m_max; //max distance from the target
    int m_seed; //each walker will have it's own seed
    gsl_rng* m_rng; //and own random generator

    public:

    //constructeurs
    DiscreteWalker();
    DiscreteWalker(std::string name, int d, std::vector<long> pos,int seed);

    //destucteurs
    ~DiscreteWalker();

    //un printeur d'état
    virtual void print_details() const;

    //fonctions getters
    long get_pos() const ;
    long get_max() const ;
    long get_min() const ;
    long get_lifetime() const ;
    int get_seed() const ;

    //fonctions setters
    void set_pos(std::vector<long> &pos);
    void set_max(long max);
    void set_lifetime(long lifetime);
    void set_seed(long seed);

    //other setter functions
    //void set_random_pos(long N);

    virtual void move(int verbose=0); //only virtual function a priori
    bool isAlive() const;
    void move_til_death(int verbose=0);
    /*
    void move_til_death_bounded(long N,int verbose=0);
    long move_til_death_bounded_record_territory(long N,int verbose=0);
    int move_fixed_max(long borne);
    double split_prob(long s0, long s1,long s2, long const n);
    double max_prob(long s0,long s1, long const n);
    */
    int move_fixed_time(long time);

};

//on surcharge ici pour eviter de redeclarer des vecteurs inutiles
double
euclidian_distance(const std::vector<long> &a,const std::vector<long> &b);

double
euclidian_distance(const std::vector<long> &a);
