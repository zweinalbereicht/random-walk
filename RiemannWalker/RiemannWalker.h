#ifndef DEF_DISCRETEWALKER
#define DEF_DISCRETEWALKER

#include <iostream>
#include <string>
#include <math.h>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>

class RiemannWalker
{

    //useful attributes for the walker
    private:

    std::string m_name;
    long m_pos;
    long m_lifetime;
    long m_min;
    long m_max;
    int m_seed; //each walker will have it's own seed
    double m_c; //general step scale
    double m_alpha; //Levy exponent
    gsl_rng* m_rng;


    public:

    //constructeurs
    RiemannWalker();
    RiemannWalker(std::string name, long pos,double c,double m_alpha ,int seed);


    //destucteurs
    ~RiemannWalker();

    //un printeur d'état
    void print_details() const;

    //fonctions getters
    long get_pos() const ;
    long get_max() const ;
    long get_min() const ;
    long get_lifetime() const ;
    double get_c() const ;
    double get_alpha() const ;

    //fonctions setters
    void set_pos(long pos);
    void set_max(long max);
    void set_min(long min);
    void set_lifetime(long lifetime);
    void set_c(double c);
    void set_alpha(double alpha);

    void move(int verbose);
    bool isAlive() const;
    void move_til_death(int verbose);
    int move_fixed_max(long borne);
    int move_fixed_time(long time);
    double split_prob(long s0, long s1,long s2, int n);

};


#endif
