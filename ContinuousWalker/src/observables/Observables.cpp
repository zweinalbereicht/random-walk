#include <pybind11/pybind11.h>
#include <pybind11/iostream.h>
#include <pybind11/numpy.h>
#include <pybind11/stl.h>
#include <iostream>
#include <vector>
#include <string>
#include <stdlib.h>
#include <gsl/gsl_rng.h>

#include "../walkers/ContinuousWalker.h"
#include "../walkers/GammaWalker.h"
#include "../walkers/LaplaceWalker.h"
#include "../walkers/LevyWalker.h"

using namespace std;

double
survival_probability(const double x0,const long n, ContinuousWalker &walker, const long N){
    double probability = 0.0;

    for(int i=0;i<N;i++){
        walker.set_lifetime(0);
        walker.set_pos(x0);
        long elapsed_time = 0;
        while(walker.isAlive() && elapsed_time<n){
            walker.move();
        }
        probability+=walker.isAlive();
    }

    return probability/((double) N);
}

double
splitting_probability(const double x0,const double x,ContinuousWalker &walker, const long N){
    double probability = 0.0;

    for(int i=0;i<N;i++){
        walker.set_lifetime(0);
        walker.set_pos(x0);
        long elapsed_time = 0;
        //encore une fois attention aux inegalités
        //en convention crossing
        while(walker.get_pos()<x && walker.get_pos()>=0){
            walker.move();
        }
        probability+=(walker.isAlive());
    }

    return probability/((double) N);
}
