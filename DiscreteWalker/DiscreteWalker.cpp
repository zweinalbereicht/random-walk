#include <iostream>
#include <vector>
#include <string>
#include <math.h>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>
#include <pybind11/pybind11.h>
#include <stdlib.h>

#include "DiscreteWalker.h"
#include "BiasedWalker.h"
#include "SATWWalker.h"
//#include "LevyWalker.h"
//#include "LaplaceWalker.h"

using namespace std;
namespace py = pybind11;


DiscreteWalker::DiscreteWalker(){
    m_name="a simple walker";
    m_pos=1;
    m_max=m_pos;
    m_min=m_pos;
    m_lifetime=0;
    m_seed=1;
    m_rng = gsl_rng_alloc(gsl_rng_mt19937);
    gsl_rng_set(m_rng,m_seed);
}

DiscreteWalker::DiscreteWalker(string name, long pos,int seed): m_name(name),m_pos(pos),m_max(pos), m_min(pos), m_seed(seed),m_lifetime(0)
{
    m_rng = gsl_rng_alloc(gsl_rng_mt19937);
    gsl_rng_set(m_rng,seed);
}

DiscreteWalker::~DiscreteWalker()
{
    gsl_rng_free(m_rng);
}

void DiscreteWalker::print_details() const
{
    cout << "name : " << m_name << endl;
    cout << "position : " << m_pos << endl;
    cout << "maximum : " << m_max << endl;
    cout << "minimum : " << m_min << endl;
    cout << "age : " << m_lifetime << endl;
    cout << "seed : " << m_seed << endl;
}

//getters
long DiscreteWalker::get_pos() const {
    return m_pos;
}

long DiscreteWalker::get_max() const {
    return m_max;
}

long DiscreteWalker::get_min() const {
    return m_min;
}

long DiscreteWalker::get_lifetime() const {
    return m_lifetime;
}

int DiscreteWalker::get_seed() const {
    return m_seed;
}

//setters
void  DiscreteWalker::set_pos(long pos){
     m_pos=pos;
}

void  DiscreteWalker::set_max(long max){
    m_max=max;
}

void  DiscreteWalker::set_min(long min){
    m_min=min;
}

void  DiscreteWalker::set_lifetime(long lifetime){
    m_lifetime=lifetime;
}

void  DiscreteWalker::set_seed(long seed){
    m_seed=seed;
    gsl_rng_set(m_rng,m_seed);
}

//the basic move function
void DiscreteWalker::move(int verbose=0){
    int m = gsl_ran_bernoulli(m_rng, 0.5); //the basic move is +1 or -1 with equal probability
    m_pos+=1-2*m;
    m_lifetime+=1;
    if(m_pos>m_max){
        m_max=m_pos;
    }
    else if(m_min>m_pos){
        m_min=m_pos;
    }
    if(verbose==1){
        cout << "position : " << m_pos << endl;
    }
}

//other funtions
void DiscreteWalker::move_til_death(int verbose=0){
    while(isAlive()){
        move(verbose);
    }
}

bool DiscreteWalker::isAlive() const
{
    return (m_pos>0); //strict inequality here
}

int DiscreteWalker::move_fixed_max(long borne)
{
    while(isAlive() && m_pos<=borne){
        move();
    }
    if (!isAlive() && m_max==borne){
        return 0; //if success
    }
    else{
        return 1;
    }
}
int  DiscreteWalker::move_fixed_time(long time)
{

    while(isAlive() && m_lifetime<=time){
        move();
    }
    if (!isAlive() && m_lifetime==time){
        return 0; //if success
    }
    else{
        return 1;
    }
}


double DiscreteWalker::split_prob(long s0, long s1,long s2, long const n)
{
    long i;
    //int result[n];
    vector<int> result(n); //encore une autre version, ne pas oublier le #include <vector> en haut sinon ça ne marche pas.
    //result=(int*) malloc(sizeof(int)*n); old C version
    for(i=0;i<n;i++){
        m_lifetime=0;
        m_pos=s0;
        while(m_pos>s1 && m_pos<s2){ //attention aux inegalités ici, c'est strict, on s'arrete lorsque l'on touche
            move(0);
        }
        result[i]=(int)(m_pos>=s2); //same thing here, watch the strictness
    }
    double m=0;
    for(i=0;i<n;i++){
        m+=result[i];
    }
    cout << m << endl;
    //free(result); old C version, using fixed size declaration in the above
    return (double)(m/n);
}

double DiscreteWalker::max_prob(long s0, long s1,long const n)
{
    long i;
    //int result[n];
    vector<int> result(n); //encore une autre version, ne pas oublier le #include <vector> en haut sinon ça ne marche pas.
    //result=(int*) malloc(sizeof(int)*n); old C version
    for(i=0;i<n;i++){
        m_lifetime=0;
        m_pos=s0;
        m_max=m_pos;
        while(m_pos>0 && m_pos<=s1){ //attention aux inegalités ici, c'est strict, on s'arrete lorsque l'on touche
            move(0);
        }
        result[i]=(int)(m_max==s1); //same thing here, watch the strictness
    }
    double m=0;
    for(i=0;i<n;i++){
        m+=result[i];
    }
    cout << m << endl;
    //free(result); old C version, using fixed size declaration in the above
    return (double)(m/n);
}


PYBIND11_MODULE(module_DiscreteWalker,handle){

    handle.doc()="this is our C++ module for continuous 1 dimensional walkers";

    py::class_<DiscreteWalker>(
                handle, "DiscreteWalker"
            )
            .def(py::init<>(),"default constructor")
            .def(py::init<string,long,int>(),"takes entry name(string), position(long), random seed(int)")

            .def("print_details",&DiscreteWalker::print_details,
                    "a function that prints details on the walker")

            .def("get_pos",&DiscreteWalker::get_pos,
                    "a getter function for the  walker's position")

            .def("get_min",&DiscreteWalker::get_min,
                    "a getter function for the  walker's minimum")

            .def("get_max",&DiscreteWalker::get_max,
                    "a getter function for the  walker's maximum")

            .def("get_lifetime",&DiscreteWalker::get_lifetime,
                    "a getter function for the  walker's lifetime")

            .def("get_seed",&DiscreteWalker::get_seed,
                    "a getter function for the  walker's seed")

            .def("set_pos",&DiscreteWalker::set_pos,
                    "a setter function for the  walker's positonn")

            .def("set_min",&DiscreteWalker::set_min,
                    "a setter function for the  walker's minimum")

            .def("set_max",&DiscreteWalker::set_max,
                    "a setter function for the  walker's maximum")

            .def("set_lifetime",&DiscreteWalker::set_lifetime,
                    "a setter function for the  walker's lifetime")

            .def("set_seed",&DiscreteWalker::set_seed,
                    "a setter function for the  walker's seed")

            .def("move",
                    &DiscreteWalker::move,
                    "a function that makes the walker perform a single step, the default choice being up or down with prob 1/2",
                    py::arg("verbose")=0)

            .def("move_til_death",&DiscreteWalker::move_til_death,
                    "a function that makes the walker walk until it reaches zero",
                    py::arg("verbose")=0)

            .def("isAlive",&DiscreteWalker::isAlive,
                    "a function that says if the walker is still alive")

            .def("move_fixed_max",&DiscreteWalker::move_fixed_max,
                    "a function that makes the walker walk until death with two absorbing boundaries. If the function returns 0 than tha walker has exactly reached the fixed max value without bypassing it, 1 else.")

            .def("move_fixed_time",&DiscreteWalker::move_fixed_time,
                    "a function that makes the walker for a fixed time period. The function returns 0 if the walker died exactly on its nth step, 1 else.")

            .def("split_prob",&DiscreteWalker::split_prob,
                    "args : (s0,s1,s2,n) -  a function that returns the splitting probability to reach s2 before s1 starting from s0, averaged over n trials.")

            .def("max_prob",&DiscreteWalker::max_prob,
                    "args : (s0,s1,n) -  a function that returns the probability that the max is esual to s1, starting from s0, averaged over n trials.")
            ;

    //Biased walker bindings
    py::class_<BiasedWalker,DiscreteWalker>(handle, "BiasedWalker")
        .def(py::init<>(),"default constructor")
        .def(py::init<double>(),"takes entry p(double)")
        .def(py::init<string,long,int,double>(),"takes entry initial position(long), random seed(int), p(double)")
        .def("print_details",&BiasedWalker::print_details,
                "a function that prints details on the walker")
        .def("get_p",&BiasedWalker::get_p,
                "a getter function for the  walker's p")
        .def("set_p",&BiasedWalker::set_p,
                "a setter function for the  walker's p")
        .def("move",&BiasedWalker::move,"a function that makes the walker perform a single step",py::arg("verbose")=0)
        ;

    //SATW walker bindings
    py::class_<SATWWalker,DiscreteWalker>(handle, "SATWWalker")
        .def(py::init<>(),"default constructor")
        .def(py::init<double>(),"takes entry beta(double)")
        .def(py::init<string,long,int,double>(),"takes entry initial position(long), random seed(int), beta(double)")
        .def("print_details",&SATWWalker::print_details,
                "a function that prints details on the walker")
        .def("get_beta",&SATWWalker::get_beta,
                "a getter function for the  walker's beta")
        .def("set_beta",&SATWWalker::set_beta,
                "a setter function for the  walker's beta")
        .def("move",&SATWWalker::move,"a function that makes the walker perform a single step",py::arg("verbose")=0)
        ;

}
