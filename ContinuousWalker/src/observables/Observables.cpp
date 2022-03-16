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
        while(walker.isAlive() && walker.get_lifetime()<n){
            walker.move();
        }
        probability+=walker.isAlive();
    }

    return probability/((double) N);
}

//renvoie la probability d'etre toujours en vie après n pas dans un intervalle
double
survival_probability_bounded(const double x0, const double x, const long n, ContinuousWalker &walker, const long N){

    double probability = 0.0;
    for(int i=0;i<N;i++){
        walker.set_lifetime(0);
        walker.set_pos(x0);
        while(walker.isAlive() && walker.get_pos()<=x && walker.get_lifetime()<n){
            walker.move();
        }
        probability+=(walker.isAlive() && walker.get_pos()<=x);
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
        while(walker.get_pos()<=x && walker.get_pos()>=0){
            walker.move();
        }
        probability+=(walker.isAlive());
    }

    return probability/((double) N);
}

//splitting probability when both boundaries are escaping, with signed speeds vleft and vright
double
splitting_probability_escaping_boundaries(const double x0,const double x,const double vleft, const double vright,ContinuousWalker &walker, const long N){
    double probability = 0.0;

    for(int i=0;i<N;i++){
        double right_boundary=x;
        double left_boundary=0;
        walker.set_lifetime(0);
        walker.set_pos(x0);
        long elapsed_time = 0;
        //encore une fois attention aux inegalités
        //en convention crossing
        while(walker.get_pos()<=right_boundary && walker.get_pos()>=left_boundary){
            walker.move();
            right_boundary+=vright;
            left_boundary+=vleft;
        }
        probability+=(walker.get_pos()>right_boundary);
    }

    return probability/((double) N);
}
//renvoie la probabilité d'observer une trajectoire de type strip, dont le max est plus grand que x
double
strip_probability(double x, ContinuousWalker &walker, const long nbSteps, const long nbSimus){

    double probability = 0.0;

    for(int i=0;i<nbSimus;i++){
        walker.set_lifetime(0);
        walker.set_pos(0);
        walker.set_max(0);
        walker.set_min(0);
        //encore une fois attention aux inegalités
        //en convention crossing
        while(walker.isAlive() && walker.get_lifetime()<nbSteps){
            walker.move();
        }
        double max=walker.get_max();
        // si on sort de la boucle en mourrant ce n'est pas tres grave, la condition ne sera jamais satisfaite dans tous les cas.
        probability+=(walker.get_pos()==max && max>x);
    }
    return probability/((double) nbSimus);
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
            //cout << walker.get_lifetime() << endl;
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

//renvoie la probabilité de sortir à travers 0 au temps n exactement
double
fpt_probability(const double x0, ContinuousWalker &walker, const long n,const long N){

    double probability;

    for(long i=0;i<N;i++){
        walker.set_lifetime(0);
        walker.set_pos(x0);
        while(walker.get_pos()>=0 && walker.get_lifetime()<n){ //on bouge jusqu'à traverser 0
            walker.move();
        }
        if(!walker.isAlive() && walker.get_lifetime()==n){ //si on sort en zero
            probability+=1;
        }
    }
    return probability/((double) N);
}

//renvoie la probabilité de sortir coté target au temps n exactement
double
conditional_fpt_probability(const double x0,const double x, ContinuousWalker &walker, const long n,const long N,const bool target){

    double probability;

    for(long i=0;i<N;i++){
        walker.set_lifetime(0);
        walker.set_pos(x0);
        while(walker.get_pos()<=x && walker.get_pos()>=0 && walker.get_lifetime()<n){ //on bouge jusqu'à sortir de l'intervalle mais on ne bouge pas plus que le temps n
            walker.move();
        }
        if(target==0 && !walker.isAlive() && walker.get_lifetime()==n){ //si on sort en zero
            probability+=1;
        }
        else if(target==1 && walker.get_pos()>x && walker.get_lifetime()==n){ //si on sort en x
            probability+=1;
        }
    }

    return probability/((double) N);
}

//renvoie la probabilité de sortir d'un intervalle au temps n exactement
double
unconditional_fpt_probability(const double x0,const double x, ContinuousWalker &walker, const long n,const long N){

    double probability;

    for(long i=0;i<N;i++){
        walker.set_lifetime(0);
        walker.set_pos(x0);
        while(walker.get_pos()<=x && walker.get_pos()>=0 && walker.get_lifetime()<n){ //on bouge jusqu'à sortir de l'intervalle mais on ne bouge pas plus que le temps n
            walker.move();
        }
        if(walker.get_lifetime()==n){ //si on sort pile après le bon nombre de pas
            if (!walker.isAlive() || walker.get_pos()>x){
                probability+=1;
            }
        }
    }

    return probability/((double) N);


}

py::list
max_on_last_step_distribution(const double x0, ContinuousWalker &walker, const long n,const long N,const bool bounded_below){

    vector<double> result(N);
    long nb_success = 0;

    while(nb_success < N){
        walker.set_lifetime(0);
        walker.set_pos(x0);
        walker.set_max(x0);
        walker.set_min(x0);
        // si il n'y a pas de bord absorbant en zero
        if (!bounded_below){
            walker.move_fixed_time(n);
            if(walker.get_max()==walker.get_pos()){ // si le max est atteint au dernier pas
                result[nb_success]=walker.get_pos();
                nb_success++;
            }
        }
        // s'il y a une barriere absorbante en 0
        else {
            while(walker.get_lifetime()<n && walker.isAlive()){
                walker.move();
            }
            if(walker.isAlive() && walker.get_max()==walker.get_pos()){ // si le max est atteint au dernier pas
                result[nb_success]=walker.get_pos();
                nb_success++;
            }
        }
    }
    py::list ret = py::cast(result);
    return ret;
}

//renvoie la distribution du max avant de traverser 0 pour la premiere fois, s'il est atteint au n-ième pas.  
py::list
time_conditioned_max_before_exit_distribution(const double x0, ContinuousWalker &walker, const long n,const long N){

    vector<double> result(N);
    long nb_success = 0;

    while(nb_success < N){
        walker.set_lifetime(0);
        walker.set_pos(x0);
        walker.set_max(x0);
        walker.set_min(x0);
        // si il n'y a pas de bord absorbant en zero
        walker.move_fixed_time(n);
        double currentMax=walker.get_max();
        if(currentMax==walker.get_pos() && walker.get_min()>=0){ // si on est au max et pas encore mort
            //si on fait un move til death ici ce sera trop long, on fait un move fixed max (en gros c'est un move til death bounded, mais pas tout à fait)
            int exitSide = walker.move_fixed_max(currentMax); // exitside egal 0 si on traverse d'abord 0
            if(!exitSide){ // si le max n'a pas été dépassé
                result[nb_success]=currentMax;
                nb_success++;
            }
        }
    }
    py::list ret = py::cast(result);
    return ret;
}

py::list
time_conditioned_max_distribution(const double x0, ContinuousWalker &walker, const long n,const long nMax,const long N){

    vector<double> result(N);
    long nb_success = 0;

    while(nb_success < N){
        walker.set_lifetime(0);
        walker.set_pos(x0);
        walker.set_max(x0);
        walker.set_min(x0);
        // si il n'y a pas de bord absorbant en zero
        walker.move_fixed_time(n);
        double currentMax=walker.get_max();
        if(currentMax==walker.get_pos()){ // si on est au max
            walker.move_fixed_time(nMax-n);
            if(currentMax==walker.get_max()){ // si le max n'a pas été dépassé
                result[nb_success]=currentMax;
                nb_success++;
            }
        }
    }
    py::list ret = py::cast(result);
    return ret;
}
