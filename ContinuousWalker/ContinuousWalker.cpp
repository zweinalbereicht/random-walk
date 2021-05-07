#include <iostream>
#include <string>
#include <math.h>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>
#include <pybind11/pybind11.h>
#include <stdlib.h>

#include "ContinuousWalker.h"
#include "LevyWalker.h"

using namespace std;
namespace py = pybind11;


ContinuousWalker::ContinuousWalker(){
    m_name="a simple walker";
    m_pos=1.0;
    m_max=m_pos;
    m_min=m_pos;
    m_lifetime=0;
    m_seed=1;
    m_rng = gsl_rng_alloc(gsl_rng_mt19937);
    gsl_rng_set(m_rng,m_seed);
}

ContinuousWalker::ContinuousWalker(string name, double pos,int seed): m_name(name),m_pos(pos),m_max(pos), m_min(pos), m_seed(seed),m_lifetime(0)
{
    m_rng = gsl_rng_alloc(gsl_rng_mt19937);
    gsl_rng_set(m_rng,seed);
}

ContinuousWalker::~ContinuousWalker()
{
    gsl_rng_free(m_rng);
}

void ContinuousWalker::print_details() const
{
    cout << "name : " << m_name << endl;
    cout << "position : " << m_pos << endl;
    cout << "maximum : " << m_max << endl;
    cout << "minimum : " << m_min << endl;
    cout << "age : " << m_lifetime << endl;
}

//getters
double ContinuousWalker::get_pos() const {
    return m_pos;
}

double ContinuousWalker::get_max() const {
    return m_max;
}

double ContinuousWalker::get_min() const {
    return m_min;
}

long ContinuousWalker::get_lifetime() const {
    return m_lifetime;
}

//setters
void  ContinuousWalker::set_pos(double pos){
     m_pos=pos;
}

void  ContinuousWalker::set_max(double max){
    m_max=max;
}

void  ContinuousWalker::set_min(double min){
    m_min=min;
}

void  ContinuousWalker::set_lifetime(long lifetime){
    m_lifetime=lifetime;
}

//the basic move function
void ContinuousWalker::move(int verbose=0){
    double m = gsl_ran_gaussian(m_rng, 1.0); //the basic move is a gaussian step
    m_pos=m_pos+((double) m);
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
void ContinuousWalker::move_til_death(int verbose=0){
    while(isAlive()){
        move(verbose);
    }
}

bool ContinuousWalker::isAlive() const
{
    return (m_pos>0);
}

int ContinuousWalker::move_fixed_max(double borne)
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
int  ContinuousWalker::move_fixed_time(long time)
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


double ContinuousWalker::split_prob(double s0, double s1,double s2, int n)
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


PYBIND11_MODULE(module_ContinuousWalker,handle){

    handle.doc()="this is our C++ module for continuous 1 dimensional walkers";

    py::class_<ContinuousWalker>(
                handle, "ContinuousWalker"
            )
            .def(py::init<>())
            .def(py::init<string,double,int>())

            .def("print_details",&ContinuousWalker::print_details,
                    "a function that prints details on the walker")

            .def("get_pos",&ContinuousWalker::get_pos,
                    "a getter function for the  walker's position")

            .def("get_min",&ContinuousWalker::get_min,
                    "a getter function for the  walker's minimum")

            .def("get_max",&ContinuousWalker::get_max,
                    "a getter function for the  walker's maximum")

            .def("get_lifetime",&ContinuousWalker::get_lifetime,
                    "a getter function for the  walker's lifetime")

            .def("set_pos",&ContinuousWalker::set_pos,
                    "a setter function for the  walker's positonn")

            .def("set_min",&ContinuousWalker::set_min,
                    "a setter function for the  walker's minimum")

            .def("set_max",&ContinuousWalker::set_max,
                    "a setter function for the  walker's maximum")

            .def("set_lifetime",&ContinuousWalker::set_lifetime,
                    "a setter function for the  walker's lifetime")

            .def("move",
                    &ContinuousWalker::move,
                    "a function that makes the walker perform a single step, the default choice being a the normal distribution",
                    py::arg("verbose")=0)

            .def("move_til_death",&ContinuousWalker::move_til_death,
                    "a function that makes the walker walk until it reaches zero",
                    py::arg("verbose")=0)

            .def("isAlive",&ContinuousWalker::isAlive,
                    "a function that says if the walker is still alive")

            .def("move_fixed_max",&ContinuousWalker::move_fixed_max,
                    "a function that makes the walker walk until death with two absorbing boundaries. If the function returns 0 than tha walker has exactly reached the fixed max value without bypassing it, 1 else.")

            .def("move_fixed_time",&ContinuousWalker::move_fixed_time,
                    "a function that makes the walker for a fixed time period. The function returns 0 if the walker died exactly on its nth step, 1 else.")

            .def("split_prob",&ContinuousWalker::split_prob,
                    "a function that returns the splitting probability to reach s2 before s1 starting from s0, averaged over n trials.")
            ;

    py::class_<LevyWalker,ContinuousWalker>(handle, "LevyWalker")
        .def(py::init<>())
        .def(py::init<double,double>())
        .def(py::init<string,double,int,double,double>())
        .def("move",&LevyWalker::move,"a function that makes the walker perform a single step",py::arg("verbose")=0)
        ;

}
