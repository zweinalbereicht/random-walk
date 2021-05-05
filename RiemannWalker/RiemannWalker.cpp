#include <iostream>
#include <string>
#include <math.h>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>
#include <pybind11/pybind11.h>
#include <stdlib.h>

#include "RiemannWalker.h"

using namespace std;
namespace py = pybind11;


RiemannWalker::RiemannWalker(){
    m_name="a simple walker";
    m_pos=1;
    m_max=m_pos;
    m_min=m_pos;
    m_lifetime=0;
    m_seed=1;
    m_c=2.0; //standard choice for lattice walks
    m_alpha=2.0; //finite variance in this case
    m_rng = gsl_rng_alloc(gsl_rng_mt19937);
    gsl_rng_set(m_rng,m_seed);
}

RiemannWalker::RiemannWalker(string name, long pos, double c,double alpha,int seed): m_name(name),m_pos(pos), m_c(c),m_alpha(alpha),m_max(pos), m_min(pos), m_seed(seed),m_lifetime(0)
{
    m_rng = gsl_rng_alloc(gsl_rng_mt19937);
    gsl_rng_set(m_rng,seed);
}

RiemannWalker::~RiemannWalker()
{
    gsl_rng_free(m_rng);
}

void RiemannWalker::print_details() const
{
    cout << "name : " << m_name << endl;
    cout << "position : " << m_pos << endl;
    cout << "maximum : " << m_max << endl;
    cout << "minimum : " << m_min << endl;
    cout << "age : " << m_lifetime << endl;
    cout << "c : " << m_c << endl;
    cout << "alpha: " << m_alpha << endl;
}

//setters
long RiemannWalker::get_pos() const {
    return m_pos;
}

long RiemannWalker::get_max() const {
    return m_max;
}

long RiemannWalker::get_min() const {
    return m_min;
}

long RiemannWalker::get_lifetime() const {
    return m_lifetime;
}

double RiemannWalker::get_c() const {
    return m_c;
}

double RiemannWalker::get_alpha() const {
    return m_alpha;
}
//getters
void  RiemannWalker::set_pos(long pos){
     m_pos=pos;
}

void  RiemannWalker::set_max(long max){
    m_max=max;
}

void  RiemannWalker::set_min(long min){
    m_min=min;
}

void  RiemannWalker::set_lifetime(long lifetime){
    m_lifetime=lifetime;
}

void  RiemannWalker::set_c(double c){
    m_c=c;
}

void  RiemannWalker::set_alpha(double alpha){
    m_alpha=alpha;
}

//the basic move function
void RiemannWalker::move(int verbose=0){
    double m = round(gsl_ran_levy(m_rng,m_c,m_alpha));
    m_pos=m_pos+((long) m);
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
void RiemannWalker::move_til_death(int verbose=0){
    while(isAlive()){
        move(verbose);
    }
}

bool RiemannWalker::isAlive() const
{
    return (m_pos>0);
}

int RiemannWalker::move_fixed_max(long borne)
{
    while(isAlive() && m_pos<=borne){
        move();
    }
    if (!isAlive() && m_max==borne){
        return 0;
    }
    else{
        return 1;
    }
}
int  RiemannWalker::move_fixed_time(long time)
{

    while(isAlive() && m_lifetime<=time){
        move();
    }
    if (!isAlive() && m_lifetime==time){
        return 0;
    }
    else{
        return 1;
    }
}


double RiemannWalker::split_prob(long s0, long s1,long s2, int n)
{
    int i;
    int* result;
    result=(int*) malloc(sizeof(int)*n);
    for(i=0;i<n;i++){
        m_lifetime=0;
        m_pos=s0;
        while(m_pos>s1 && m_pos<s2){
            move();
        }
        result[i]=(int)(m_pos>=s2);
    }
    double m=0;
    for(i=0;i<n;i++){
        m+=result[i];
    }
    free(result);
    return (double)(m/n);
}


PYBIND11_MODULE(module_RiemannWalker,handle){

    handle.doc()="this is our C++ module for discrete walkers";

    py::class_<RiemannWalker>(
                handle, "RiemannWalker"
            )
            .def(py::init<>())
            .def(py::init<string,long,double,double,int>())

            .def("print_details",&RiemannWalker::print_details,
                    "a function that prints details on the walker")

            .def("get_pos",&RiemannWalker::get_pos,
                    "a getter function for the  walker's position")

            .def("get_min",&RiemannWalker::get_min,
                    "a getter function for the  walker's minimum")

            .def("get_max",&RiemannWalker::get_max,
                    "a getter function for the  walker's maximum")

            .def("get_lifetime",&RiemannWalker::get_lifetime,
                    "a getter function for the  walker's lifetime")

            .def("get_c",&RiemannWalker::get_c,
                    "a getter function for the  walker's c parameter")

            .def("get_alpha",&RiemannWalker::get_alpha,
                    "a getter function for the  walker's alpha parameter")

            .def("set_pos",&RiemannWalker::set_pos,
                    "a setter function for the  walker's positonn")

            .def("set_min",&RiemannWalker::set_min,
                    "a setter function for the  walker's minimum")

            .def("set_max",&RiemannWalker::set_max,
                    "a setter function for the  walker's maximum")

            .def("set_lifetime",&RiemannWalker::set_lifetime,
                    "a setter function for the  walker's lifetime")

            .def("set_c",&RiemannWalker::set_c,
                    "a setter function for the  walker's c parameter")

            .def("set_alpha",&RiemannWalker::set_alpha,
                    "a setter function for the  walker's alpha parameter")

            .def("move",
                    &RiemannWalker::move,
                    "a function that makes the walker perform a single step",
                    py::arg("verbose")=0)

            .def("move_til_death",&RiemannWalker::move_til_death,
                    "a function that makes the walker walk until it reaches zero",
                    py::arg("verbose")=0)

            .def("isAlive",&RiemannWalker::isAlive,
                    "a function that says if the walker is still alive")

            .def("move_fixed_max",&RiemannWalker::move_fixed_max,
                    "a function that makes the walker walk until death with two absorbing boundaries. If the function returns 0 than tha walker has exactly reached the fixed max value without bypassing it, 1 else.")

            .def("move_fixed_time",&RiemannWalker::move_fixed_time,
                    "a function that makes the walker for a fixed time period. The function returns 0 if the walker died exactly on its nth step, 1 else.")

            .def("split_prob",&RiemannWalker::split_prob,
                    "a function that returns the splitting probability to reach s2 before s1 starting from s0, with n trials.")

        ;
}
