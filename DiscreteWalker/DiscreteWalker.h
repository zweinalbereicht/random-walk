#ifndef DEF_DISCRETEWALKER
#define DEF_DISCRETEWALKER

#include <iostream>
#include <string>
#include <math.h>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>

class DiscreteWalker
{

    //useful attributes for the walker
    private:

    std::string m_name;
    long m_pos;
    long m_lifetime;
    long m_min;
    long m_max;
    int m_seed; //each walker will have it's own seed
    gsl_rng* m_rng;


    public:

    //constructeurs
    DiscreteWalker();
    DiscreteWalker(std::string name, long pos, int seed);


    //destucteurs
    ~DiscreteWalker();

    //un printeur d'état
    void print_details() const;

    //fonctions getters
    long get_pos() const ;
    long get_max() const ;
    long get_min() const ;
    long get_lifetime() const ;

    //fonctions setters
    void set_pos(long pos);
    void set_max(long max);
    void set_min(long min);
    void set_lifetime(long lifetime);

    void move();
    bool isAlive() const;
    void move_til_death();
    int move_fixed_max(long borne);
    int move_fixed_time(long time);

};


#endif
