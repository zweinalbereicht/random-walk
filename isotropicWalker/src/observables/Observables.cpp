#include <pybind11/pybind11.h>
#include <pybind11/iostream.h>
#include <pybind11/numpy.h>
#include <pybind11/stl.h>
#include <iostream>
#include <vector>
#include <string>
#include <stdlib.h>
#include <gsl/gsl_rng.h>

#include "../walkers/GaussianWalker.h"

#include "Observables.h"

#define LOG(x) cout << x << endl;

using namespace std;
namespace py = pybind11;

double
split_prob_hyperplane(const double x0,const double x, GaussianWalker &walker, const int n)
{
    vector<int> result_tmp(n);
    double run=0;
    for(int i=0;i<n;i++)
    {
        //prepare for the run
        walker.set_lifetime(0);
        walker.set_coord(0,x0);
        int d=walker.get_dimension();
        for(int k=1;k<d;k++)
            walker.set_coord(k,0.0);

        //run
        while(walker.get_pos()[0]>=0 && walker.get_pos()[0]<=x)
        {
            walker.move();
        }
        run+=(walker.get_pos()[0]>0);
    }
    return(run/((double) n));
}
