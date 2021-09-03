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
namespace py = pybind11;

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

py::list
conditional_fpt_distribution(const double x0,const double x, ContinuousWalker &walker, const long N,const bool target){

    vector<long> result(N);
    long nb_success = 0;

    while(nb_success < N){
        walker.set_lifetime(0);
        walker.set_pos(x0);
        while(walker.get_pos()<=x && walker.get_pos()>=0){ //on bouge jusqu'à sortir de l'intervalle
            walker.move();
        }
        if(target==0 && !walker.isAlive()){ //si on sort en zero
            cout << walker.get_lifetime() << endl;
            result[nb_success]=walker.get_lifetime();
            nb_success++;
        }
        else if(target==1 && walker.isAlive()){ //si on sort en x
            result[nb_success]=walker.get_lifetime();
            nb_success++;
        }
    }

    py::list ret = py::cast(result);
    return ret;

}

//renvoie la moyenne du temps de passage conditionnel à travers target(0=0,1=x), entre x et 0 
double
conditional_fpt_mean(const double x0,const double x, ContinuousWalker &walker, const long N,const bool target){

    vector<long> result;
    long nb_success = 0;
    double mean=0.0;

    while(nb_success <= N){
        walker.set_lifetime(0);
        walker.set_pos(x0);
        while(walker.get_pos()<=x && walker.get_pos()>=0){ //on bouge jusqu'à sortir de l'intervalle
            walker.move();
        }
        if(target==0 && !walker.isAlive()){ //si on sort en zero
            result.push_back(walker.get_lifetime());
            nb_success++;
        }
        else if(target==1 && walker.isAlive()){ //si on sort en x
            result.push_back(walker.get_lifetime());
            nb_success++;
        }
    }

    for(auto el : result){
        mean+=el;
    }
    return mean/((double) N);
}

