#include <iostream>
#include <string>
#include <math.h>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>
#include <pybind11/pybind11.h>

#include "SATWWalker.h"

using namespace std;
namespace py = pybind11;


SATWWalker::SATWWalker(){
    m_name="a simple walker";
    m_pos=1;
    m_max=m_pos;
    m_min=m_pos;
    m_lifetime=0;
    m_seed=1;
    m_beta=0.5;
    m_rng = gsl_rng_alloc(gsl_rng_mt19937);
    gsl_rng_set(m_rng,m_seed);
}

SATWWalker::SATWWalker(string name, long pos, double beta,int seed): m_name(name),m_pos(pos), m_beta(beta),m_max(pos), m_min(pos), m_seed(seed),m_lifetime(0)
{
    m_rng = gsl_rng_alloc(gsl_rng_mt19937);
    gsl_rng_set(m_rng,seed);
}

SATWWalker::~SATWWalker()
{
    gsl_rng_free(m_rng);
}

void SATWWalker::print_details() const
{
    cout << "name : " << m_name << endl;
    cout << "position : " << m_pos << endl;
    cout << "age : " << m_lifetime << endl;
    cout << "beta : " << m_beta << endl;
}

//setters
long SATWWalker::get_pos() const {
    return m_pos;
}

long SATWWalker::get_max() const {
    return m_max;
}

long SATWWalker::get_min() const {
    return m_min;
}

double SATWWalker::get_beta() const {
    return m_beta;
}

long SATWWalker::get_lifetime() const {
    return m_lifetime;
}

//getters
void  SATWWalker::set_pos(long pos){
     m_pos=pos;
}

void  SATWWalker::set_max(long max){
    m_max=max;
}

void  SATWWalker::set_min(long min){
    m_min=min;
}

void  SATWWalker::set_lifetime(long lifetime){
    m_lifetime=lifetime;
}

void  SATWWalker::set_beta(double beta){
    m_beta=beta;
}

//the basic move function
void SATWWalker::move(int verbose=0){
    if(m_lifetime==0){
        m_pos+=1-2*((int)gsl_rng_uniform_int(m_rng,2));
    }
    else{
        if(m_pos==m_max){
            m_pos+=1-2*((int)gsl_ran_bernoulli(m_rng,1-m_beta));
        }
        else if(m_pos==m_min){
            m_pos+=1-2*((int)gsl_ran_bernoulli(m_rng,m_beta));
        }
        else{
        m_pos+=1-2*((int)gsl_rng_uniform_int(m_rng,2));
        }
    }
    if(verbose==1){
        cout << "position : " << m_pos << endl;
    }
    m_lifetime+=1;
    if (m_pos>m_max){
        m_max=m_pos;
    }
    else if (m_pos<m_min){
        m_min=m_pos;
    }
}

void SATWWalker::move_til_death(int verbose=0){
    while(isAlive()){
        move(verbose);
    }
}

bool SATWWalker::isAlive() const
{
    return (m_pos>0);
}

int SATWWalker::move_fixed_max(long borne)
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
int  SATWWalker::move_fixed_time(long time)
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


PYBIND11_MODULE(module_SATWWalker,handle){

    handle.doc()="this is our C++ module for discrete walkers";

    py::class_<SATWWalker>(
                handle, "SATWWalker"
            )
            .def(py::init<>())
            .def(py::init<string,long,double,int>())

            .def("print_details",&SATWWalker::print_details,
                    "a function that prints details on the walker")

            .def("get_pos",&SATWWalker::get_pos,
                    "a getter function for the  walker's position")

            .def("get_min",&SATWWalker::get_min,
                    "a getter function for the  walker's minimum")

            .def("get_max",&SATWWalker::get_max,
                    "a getter function for the  walker's maximum")

            .def("get_lifetime",&SATWWalker::get_lifetime,
                    "a getter function for the  walker's lifetime")

            .def("get_beta",&SATWWalker::get_beta,
                    "a getter function for the  walker's beta parameter")

            .def("set_pos",&SATWWalker::set_pos,
                    "a setter function for the  walker's positonn")

            .def("set_min",&SATWWalker::set_min,
                    "a setter function for the  walker's minimum")

            .def("set_max",&SATWWalker::set_max,
                    "a setter function for the  walker's maximum")

            .def("set_lifetime",&SATWWalker::set_lifetime,
                    "a setter function for the  walker's lifetime")

            .def("set_beta",&SATWWalker::set_beta,
                    "a setter function for the  walker's beta parameter")

            .def("move",
                    &SATWWalker::move,
                    "a function that makes the walker perform a single step",
                    py::arg("verbose")=0)

            .def("move_til_death",&SATWWalker::move_til_death,
                    "a function that makes the walker walk until it reaches zero",
                    py::arg("verbose")=0)

            .def("isAlive",&SATWWalker::isAlive,
                    "a function that says if the walker is still alive")

            .def("move_fixed_max",&SATWWalker::move_fixed_max,
                    "a function that makes the walker walk until death with two absorbing boundaries")

            .def("move_fixed_time",&SATWWalker::move_fixed_time,
                    "a function that makes the walker for a fixed time period")

        ;
}
