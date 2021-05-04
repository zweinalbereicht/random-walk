#ifndef DEF_DISCRETEWALKER
#define DEF_DISCRETEWALKER

#include <iostream>
#include <string>
#include <math.h>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>

class SATWWalker
{

    //useful attributes for the walker
    private:

    std::string m_name;
    long m_pos;
    long m_lifetime;
    long m_min;
    long m_max;
    int m_seed; //each walker will have it's own seed
    double m_beta; //prob of discovering new site
    gsl_rng* m_rng;


    public:

    //constructeurs
    SATWWalker();
    SATWWalker(std::string name, long pos,double beta ,int seed);


    //destucteurs
    ~SATWWalker();

    //un printeur d'état
    void print_details() const;

    //fonctions getters
    long get_pos() const ;
    long get_max() const ;
    long get_min() const ;
    long get_lifetime() const ;
    double get_beta() const ;

    //fonctions setters
    void set_pos(long pos);
    void set_max(long max);
    void set_min(long min);
    void set_lifetime(long lifetime);
    void set_beta(double beta);

    void move(int verbose);
    bool isAlive() const;
    void move_til_death(int verbose);
    int move_fixed_max(long borne);
    int move_fixed_time(long time);

};


#endif
