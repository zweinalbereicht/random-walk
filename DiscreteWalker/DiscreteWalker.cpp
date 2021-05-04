#include <iostream>
#include <string>
#include <math.h>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>
#include <pybind11/pybind11.h>

#include "DiscreteWalker.h"

using namespace std;
namespace py = pybind11;


DiscreteWalker::DiscreteWalker(){
    m_name="a simple walker";
    m_pos=1;
    m_max=m_pos;
    m_min=m_pos;
    m_lifetime=1;
    m_seed=1;
    m_rng = gsl_rng_alloc(gsl_rng_mt19937);
    gsl_rng_set(m_rng,m_seed);
}

DiscreteWalker::DiscreteWalker(string name, long pos, int seed): m_name(name),m_pos(pos), m_max(pos), m_min(pos), m_seed(seed),m_lifetime(0)
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
    cout << "age : " << m_lifetime << endl;
}


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

void DiscreteWalker::move(){
    m_pos+=1-2*((int)gsl_rng_uniform_int(m_rng,2));
    m_lifetime+=1;
    if (m_pos>m_max){
        m_max=m_pos;
    }
    if (m_pos<m_min){
        m_min=m_pos;
    }
}

void DiscreteWalker::move_til_death(){
    while(isAlive()){
        move();
    }
}

bool DiscreteWalker::isAlive() const
{
    return (m_pos>0);
}

int DiscreteWalker::move_fixed_max(long borne)
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
int  DiscreteWalker::move_fixed_time(long time)
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


PYBIND11_MODULE(module_DiscreteWalker,handle){

    handle.doc()="this is our C++ module for discrete walkers";

    py::class_<DiscreteWalker>(
                handle, "pyDiscreteWalker"
            )
            .def(py::init<>())
            .def(py::init<string,long,int>())
            .def("print_details",&DiscreteWalker::print_details)
            .def("move",&DiscreteWalker::move)
            .def("move_til_death",&DiscreteWalker::move_til_death)
            .def("isAlive",&DiscreteWalker::isAlive)
            .def("get_pos",&DiscreteWalker::get_pos)
            .def("get_min",&DiscreteWalker::get_min)
            .def("get_max",&DiscreteWalker::get_max)
            .def("get_lifetime",&DiscreteWalker::get_lifetime)
            .def("set_pos",&DiscreteWalker::set_pos)
            .def("set_min",&DiscreteWalker::set_min)
            .def("set_max",&DiscreteWalker::set_max)
            .def("set_lifetime",&DiscreteWalker::set_lifetime)
            .def("move_fixed_max",&DiscreteWalker::move_fixed_max)
            .def("move_fixed_time",&DiscreteWalker::move_fixed_time)
        ;
}
