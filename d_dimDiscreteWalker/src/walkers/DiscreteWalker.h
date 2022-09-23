#pragma once

#include <iostream>
#include <random>
#include <string>
#include <math.h>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>


class DiscreteWalker
{

    //useful attributes for the walker
    protected:

    std::string m_name;
    int m_d; //the dimension of the hypercube
    std::vector<long> m_pos;
    long m_lifetime;
    double m_max; //max distance from the target
    int m_seed; //each walker will have it's own seed
    gsl_rng* m_rng; //and own random generator

    public:

    //constructeurs
    DiscreteWalker();
    DiscreteWalker(std::string name, int d, const pybind11::list &pos,int seed);

    //destucteurs
    ~DiscreteWalker();

    //un printeur d'état
    virtual void print_details() const;

    //fonctions getters
    
    pybind11::list get_pos() const ;
    long get_max() const ;
    long get_min() const ;
    long get_lifetime() const ;
    int get_seed() const ;

    //fonctions setters
    void set_pos(const pybind11::list &pos);
    void set_max(double max);
    void set_lifetime(long lifetime);
    void set_seed(long seed);

    //other setter functions
    void set_random_pos(const pybind11::list &dimensions);

    //void set_random_pos(long N);

    virtual void move(int verbose=0); //only virtual function a priori

    virtual void move_bounded(const pybind11::list &dimensions, int verbose=0); //the dimensions give the size of the hypercube we are moving in
    virtual void move_bounded(const std::vector<long> &dimensions, int verbose=0); //the dimensions give the size of the hypercube we are moving in

    bool isAlive() const;
    void move_til_death(int verbose=0);
    void move_til_death_bounded(const pybind11::list &dimensions, int verbose=0); //the dimensions give the size of the hypercube we are moving in
    long move_til_death_bounded_record_territory(const pybind11::list &dimensions,int verbose=0);
    /*
    int move_fixed_max(long borne);
    double split_prob(long s0, long s1,long s2, long const n);
    double max_prob(long s0,long s1, long const n);
    */
    int move_fixed_time(long time);

    long move_til_death_fixed_time_record_territory(const int max_time,const int verbose=0);
    long move_til_death_fixed_time(const int max_time,const int verbose=0);

};

//on surcharge ici pour eviter de redeclarer des vecteurs inutiles
double
euclidian_distance(const std::vector<long> &a,const std::vector<long> &b);

double
euclidian_distance(const std::vector<long> &a);
