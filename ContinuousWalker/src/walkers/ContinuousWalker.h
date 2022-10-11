#pragma once

#include <iostream>
#include <string>
#include <math.h>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>

class ContinuousWalker
{

    //useful attributes for the walker
    protected:

    std::string m_name;
    double m_pos;
    long m_lifetime;
    double m_min;
    double m_max;
    int m_seed; //each walker will have it's own seed
    gsl_rng* m_rng; //and own random generator


    public:

    //constructeurs
    ContinuousWalker();
    ContinuousWalker(std::string name, double pos,int seed);


    //destucteurs
    ~ContinuousWalker();

    //un printeur d'état
    void print_details() const;

    //fonctions getters
    double get_pos() const ;
    double get_max() const ;
    double get_min() const ;
    long get_lifetime() const ;
    int get_seed() const ;

    //fonctions setters
    void set_pos(double pos);
    void set_max(double max);
    void set_min(double min);
    void set_lifetime(long lifetime);
    void set_seed(long seed);

    virtual void move(int verbose=0); //only virtual function a priori
    bool isAlive() const;
    void move_til_death(int verbose=0);
    int move_fixed_max(double borne);
    void move_fixed_time(long time);
    long move_fixed_time_record_territory(long time);
    long move_til_covered(double size);
    long move_til_covered_crossing(double size);
    void move_bounded_fixed_time(double size,long time);
    double split_prob(double s0, double s1,double s2, int n);
    void move_bounded(double size, int verbose=0);
    int move_bounded_crossing(double size, int verbose=0);

};

