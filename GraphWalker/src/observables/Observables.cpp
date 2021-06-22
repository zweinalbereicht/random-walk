#include <pybind11/pybind11.h>
#include <pybind11/iostream.h>
#include <pybind11/numpy.h>
#include <pybind11/stl.h>
#include <iostream>
#include <vector>
#include <string>
#include <stdlib.h>
#include <gsl/gsl_rng.h>

#include "../walkers/GraphWalker.h"
#include "Observables.h"

using namespace std;
namespace py = pybind11;

py::list
fpt_arrival_distribution(const int s0,const int target,GraphWalker &walker, const int n)
{
    assert(s0<walker.get_graph_size()),
    assert(target<walker.get_graph_size());

    vector<int> result(n);
    for(int i=0;i<n;i++)
    {
        walker.set_lifetime(0);
        walker.set_pos(s0);
        walker.move_til_death(target);
        result[i]=walker.get_lifetime();
    }

    py::list ret = py::cast(result);
    return ret;
}

double
fpt_arrival_mean(const int s0,const int target,GraphWalker &walker, const int n)
{
    assert(s0<walker.get_graph_size()),
    assert(target<walker.get_graph_size());
    vector<long> result(n);
    for(int i=0;i<n;i++)
    {
        walker.set_lifetime(0);
        walker.set_pos(s0);
        walker.move_til_death(target);
        result[i]=walker.get_lifetime();
    }

    double m;

    for (int i=0;i<n;i++){
       m+=result[i];
    }

    return (double) m/n;
}

double
fpt_arrival_global_mean(const int target ,GraphWalker &walker, const int n)
{
    assert(target<walker.get_graph_size());

    vector<long> result(n);
    for(int i=0;i<n;i++)
    {
        walker.set_lifetime(0);
        walker.set_random_pos();
        walker.move_til_death(target);
        result[i]=walker.get_lifetime();
    }

    double m;

    for (int i=0;i<n;i++){
       m+=result[i];
    }

    return (double) m/n;
}

py::list
territory_distribution(const int s0, const int target, GraphWalker &walker, const int n)
{
    assert(s0<walker.get_graph_size()),
    assert(target<walker.get_graph_size());
    vector<long> result(n);
    for(int i=0;i<n;i++)
    {
        walker.set_lifetime(0);
        walker.set_pos(s0);
        result[i]=walker.move_til_death_record_territory(target); // a implementer
    }

    py::list ret = py::cast(result);
    return ret;
}

double
territory_mean(const int s0, const int target , GraphWalker &walker, const int n)
{
    assert(s0<walker.get_graph_size()),
    assert(target<walker.get_graph_size());
    vector<long> result(n);
    for(int i=0;i<n;i++)
    {
        walker.set_lifetime(0);
        walker.set_pos(s0);
        result[i]=walker.move_til_death_record_territory(target); // a implementer
    }

    double m;

    for (int i=0;i<n;i++){
       m+=result[i];
    }

    return (double) m/n;
}

double
territory_global_mean(const int target,GraphWalker &walker, const int n)
{
    assert(target<walker.get_graph_size());
    vector<long> result(n);
    for(int i=0;i<n;i++)
    {
        walker.set_lifetime(0);
        walker.set_random_pos();
        result[i]=walker.move_til_death_record_territory(target); // a implementer

    }

    double m;

    for (int i=0;i<n;i++){
       m+=result[i];
    }

    return (double) m/n;
}

py::list
max_dist_territory_distribution(const int s0, const int target, GraphWalker &walker,const int n,const string filename)
{
    assert(s0<walker.get_graph_size()),
    assert(target<walker.get_graph_size());

    //prepare storage data
    vector<int> territory(n);
    vector<int> max_dist(n);
    vector<int> tmp(2);

    //prepare SP matrix
    vector<int> SP=load_matrix(filename,walker.get_graph_size());

    for(int i=0;i<n;i++)
    {
        walker.set_lifetime(0);
        walker.set_pos(s0);
        walker.move_til_death_territory_max_dist(target,tmp,SP);
        territory[i]=tmp[0];
        max_dist[i]=tmp[1];
    }

    vector<vector<int>> results;
    results.push_back(territory);
    results.push_back(max_dist);
    py::list ret = py::cast(results);
    return ret;
}
