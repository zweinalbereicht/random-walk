#include <pybind11/pybind11.h>
#include <pybind11/iostream.h>
#include <pybind11/numpy.h>
#include <pybind11/stl.h>
#include <iostream>
#include <vector>
#include <string>
#include <stdlib.h>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>
#include <math.h>

#include "../walkers/DiscreteWalker.h"
#include "../walkers/BiasedWalker.h"
#include "../walkers/SATWWalker.h"
#include "../walkers/RiemannWalker.h"

#include "Observables.h"

using namespace std;
namespace py = pybind11;

py::list
fpt_arrival_bounded_distribution(const long s0,const long N,DiscreteWalker &walker, const int n)
{
    vector<long> result(n);
    for(int i=0;i<n;i++)
    {
        walker.set_lifetime(0);
        walker.set_pos(s0);
        walker.move_til_death_bounded(N);
        result[i]=walker.get_lifetime();
    }

    py::list ret = py::cast(result);
    return ret;
}

double
fpt_arrival_bounded_global_mean(const long N,DiscreteWalker &walker, const int n)
{
    vector<long> result(n);
    for(int i=0;i<n;i++)
    {
        walker.set_lifetime(0);
        walker.set_random_pos(N);
        walker.move_til_death_bounded(N);
        result[i]=walker.get_lifetime();
    }

    double m;

    for (int i=0;i<n;i++){
       m+=result[i];
    }

    return (double) m/n;
}

double
fpt_arrival_bounded_mean(const long s0,const long N,DiscreteWalker &walker, const int n)
{
    vector<long> result(n);
    for(int i=0;i<n;i++)
    {
        walker.set_lifetime(0);
        walker.set_pos(s0);
        walker.move_til_death_bounded(N);
        result[i]=walker.get_lifetime();
    }

    double m;

    for (int i=0;i<n;i++){
       m+=result[i];
    }

    return (double) m/n;
}

py::list
territory_distribution(const long s0, const long N, DiscreteWalker &walker, const int n)
{
    vector<long> result(n);
    for(int i=0;i<n;i++)
    {
        walker.set_lifetime(0);
        walker.set_pos(s0);
        result[i]=walker.move_til_death_bounded_record_territory(N); // a implementer
    }

    py::list ret = py::cast(result);
    return ret;
}

double
territory_global_mean(const long N,DiscreteWalker &walker, const int n)
{
    vector<long> result(n);
    for(int i=0;i<n;i++)
    {
        walker.set_lifetime(0);
        walker.set_random_pos(N);
        result[i]=walker.move_til_death_bounded_record_territory(N); // a implementer

    }

    double m;

    for (int i=0;i<n;i++){
       m+=result[i];
    }

    return (double) m/n;
}

double
territory_mean(const long s0,const long N,DiscreteWalker &walker, const int n)
{
    vector<long> result(n);
    for(int i=0;i<n;i++)
    {
        walker.set_lifetime(0);
        walker.set_pos(s0);
        result[i]=walker.move_til_death_bounded_record_territory(N); // a implementer
    }

    double m;

    for (int i=0;i<n;i++){
       m+=result[i];
    }

    return (double) m/n;
}

double
rosenstock_fixed_time(const long s0, DiscreteWalker &walker, const int time, const double rho, const int n,const int verbose)
{

    double m = 0.0;
    if(time<s0 || (s0+time)%2==1) //il faut avoir le temps d'aller jusqu'à 0 quand même et que la parité fonctionne bien
        return 0.0;

    int success = 0;
    double survival_probability;
    while(success<n)
    {
        walker.set_lifetime(0); //attention a bien reinitialiser ici
        walker.set_pos(s0);
        walker.set_max(s0);

        for(int i=0;i<time;i++)
        {
            walker.move(verbose);
        }
        if (walker.get_pos()==0)
        {
            m = pow(1-rho,walker.get_max());
            if (gsl_rng_uniform(walker.get_rng())<m)
            {
                survival_probability++;
            }
            success++;
        }
    }
    if(m==0) 
        return 0.0;
return survival_probability/((double) n);
}
