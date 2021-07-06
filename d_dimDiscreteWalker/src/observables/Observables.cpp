#include <pybind11/pybind11.h>
#include <pybind11/iostream.h>
#include <pybind11/numpy.h>
#include <pybind11/stl.h>
#include <iostream>
#include <vector>
#include <string>
#include <stdlib.h>
#include <gsl/gsl_rng.h>

#include "../walkers/DiscreteWalker.h"

#include "Observables.h"

using namespace std;
namespace py = pybind11;

py::list
fpt_arrival_bounded_distribution(const pybind11::list &s0,const pybind11::list &dimensions,DiscreteWalker &walker, const int n)
{
    vector<long> result(n);
    for(int i=0;i<n;i++)
    {
        walker.set_lifetime(0);
        walker.set_pos(s0);
        walker.move_til_death_bounded(dimensions);
        result[i]=walker.get_lifetime();
    }

    py::list ret = py::cast(result);
    return ret;
}

double
fpt_arrival_bounded_global_mean(const pybind11::list &dimensions,DiscreteWalker &walker, const int n)
{
    vector<long> result(n);
    for(int i=0;i<n;i++)
    {
        walker.set_lifetime(0);
        walker.set_random_pos(dimensions);
        walker.move_til_death_bounded(dimensions);
        result[i]=walker.get_lifetime();
    }

    double m;

    for (int i=0;i<n;i++){
       m+=result[i];
    }

    return (double) m/n;
}

double
fpt_arrival_bounded_mean(const pybind11::list &s0,const pybind11::list &dimensions,DiscreteWalker &walker, const int n)
{
    vector<long> result(n);
    for(int i=0;i<n;i++)
    {
        walker.set_lifetime(0);
        walker.set_pos(s0);
        walker.move_til_death_bounded(dimensions);
        result[i]=walker.get_lifetime();
    }

    double m;

    for (int i=0;i<n;i++){
       m+=result[i];
    }

    return (double) m/n;
}

py::list
territory_distribution(const pybind11::list &s0, const pybind11::list &dimensions, DiscreteWalker &walker, const int n)
{
    vector<long> result(n);
    for(int i=0;i<n;i++)
    {
        walker.set_lifetime(0);
        walker.set_pos(s0);
        result[i]=walker.move_til_death_bounded_record_territory(dimensions); // a implementer
    }

    py::list ret = py::cast(result);
    return ret;
}

double
territory_mean(const pybind11::list &s0,const pybind11::list &dimensions,DiscreteWalker &walker, const int n)
{
    vector<long> result(n);
    for(int i=0;i<n;i++)
    {
        walker.set_lifetime(0);
        walker.set_pos(s0);
        result[i]=walker.move_til_death_bounded_record_territory(dimensions);
    }

    double m;

    for (int i=0;i<n;i++){
       m+=result[i];
    }

    return (double) m/n;
}


double
territory_global_mean(const pybind11::list &dimensions, DiscreteWalker &walker, const int n)
{
    vector<long> result(n);
    for(int i=0;i<n;i++)
    {
        walker.set_lifetime(0);
        walker.set_random_pos(dimensions);
        result[i]=walker.move_til_death_bounded_record_territory(dimensions); // a implementer

    }

    double m;

    for (int i=0;i<n;i++){
       m+=result[i];
    }

    return (double) m/n;
}

