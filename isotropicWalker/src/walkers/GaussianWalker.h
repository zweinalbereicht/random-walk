#pragma once

#include <iostream>
#include <random>
#include <string>
#include <math.h>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>


class GaussianWalker
{

    //useful attributes for the walker
    protected:

    std::string m_name;
    int m_d; //the dimension of the space in which we evolve
    std::vector<double> m_direction;
    std::vector<double> m_pos;
    double m_lifetime;
    double m_max; //max distance from the origin
    int m_seed; //each walker will have it's own seed
    gsl_rng* m_rng; //and own random generator

    public:

    //constructeurs
    GaussianWalker();
    GaussianWalker(std::string name, int d, const pybind11::list &pos,int seed);

    //destucteurs
    ~GaussianWalker();

    //un printeur d'état
    virtual void print_details() const;

    //fonctions getters
    std::vector<double> get_pos() const ;
    std::vector<double> get_direction() const;
    double get_max() const ;
    double get_lifetime() const ;
    int get_seed() const ;
    int get_dimension() const ;

    //fonctions setters
    void set_pos(const pybind11::list &pos);
    void set_direction(const pybind11::list &direction);
    void set_max(double max);
    void set_lifetime(double lifetime);
    void set_seed(int seed);
    void set_coord(int c,double x); //change the value in one coordinate (useful for in C code)

    //other setter functions
    void set_random_pos(const pybind11::list &dimensions); //uniform inital pos in the box

    //void set_random_pos(long N);

    virtual void move(int verbose=0); //only virtual function a priori

    virtual void move_bounded(const pybind11::list &dimensions, int verbose=0); //the dimensions give the size of the hypercube we are moving in and we want to impose periodic boundary conditions
    //virtual void move_bounded(const std::vector<long> &dimensions, int verbose=0); //the dimensions give the size of the hypercube we are moving in and we want to impose periodic boundary conditions

    bool isAlive() const;
    void move_til_death(int verbose=0);
    void move_til_death_bounded(const pybind11::list &dimensions, int verbose=0); //the dimensions give the size of the hypercube we are moving in
    void move_fixed_time(long time); //impose a fixed number of steps (although the lifetime might be longer depending on the model)


};

//on surcharge ici pour eviter de redeclarer des vecteurs inutiles genre le vecteur nul
double
euclidian_distance(const std::vector<double> &a,const std::vector<double> &b);

double
euclidian_distance(const std::vector<double> &a);

void
sphere_direction(const int d, std::vector<double> &dir, gsl_rng* rng);
