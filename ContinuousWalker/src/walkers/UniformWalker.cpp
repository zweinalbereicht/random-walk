#include <gsl/gsl_randist.h>
#include <gsl/gsl_rng.h>
#include <iostream>
#include <math.h>
#include <pybind11/pybind11.h>
#include <stdlib.h>
#include <string>

#include "ContinuousWalker.h"
//le include precedent est il necessaire?
#include "UniformWalker.h"

using namespace std;
namespace py = pybind11;

UniformWalker::UniformWalker() : ContinuousWalker() ,m_scale(1.0)
{}

UniformWalker::UniformWalker(double scale) : ContinuousWalker(),m_scale(scale)
{}

UniformWalker::UniformWalker(string name, double pos, int seed,double scale) : ContinuousWalker(name, pos, seed) ,m_scale(scale)
{}

void UniformWalker::print_details() const
{
    ContinuousWalker::print_details();
    cout << "scale param : " << m_scale << endl;
}


double UniformWalker::get_scale() const
{
    return m_scale;
}

void UniformWalker::set_scale(const double scale)
{
    m_scale=scale;
}

void UniformWalker::move(int verbose)
{
    int dir=(int)(1-2*gsl_ran_bernoulli(m_rng,0.5));
    m_pos+=(double)(dir*gsl_rng_uniform(m_rng)*m_scale);
    m_lifetime+=1;
    if(verbose)
        cout << "pos : " << m_pos << endl;
    if (m_pos>m_max){
        m_max=m_pos;
    }
    else if (m_pos<m_min){
        m_min=m_pos;
    }
}


//PYBIND11_MODULE(module_ContinuousWalker,handle){
//    py::class_<UniformWalker,ContinuousWalker>(
//            handle, "UniformWalker"
//            )
//        .def(py::init<>())
//        .def(py::init<double,double>())
//        .def(py::init<string,double,int,double,double>())
//        .def("move",
//                &UniformWalker::move,"a function that makes the walker perform a single step",py::arg("verbose")=0)
//        ;
//}
