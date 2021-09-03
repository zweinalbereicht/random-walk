#include <iostream>
#include <string>
#include <math.h>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>
#include <pybind11/pybind11.h>
#include <stdlib.h>

#include "ContinuousWalker.h"
//le include precedent est il necessaire?
#include "GammaWalker.h"

using namespace std;
namespace py = pybind11;

GammaWalker::GammaWalker() : ContinuousWalker() ,m_scale(1.0),m_exponent(2.0)
{}

GammaWalker::GammaWalker(double scale,double exponent) : ContinuousWalker(),m_scale(scale),m_exponent(exponent)
{}

GammaWalker::GammaWalker(string name, double pos, int seed,double scale, double exponent) : ContinuousWalker(name, pos, seed) ,m_scale(scale),m_exponent(exponent)
{}

void GammaWalker::print_details() const
{
    ContinuousWalker::print_details();
    cout << "scale param : " << m_scale << endl;
    cout << "exponent param : " << m_exponent << endl;
}


double  GammaWalker::get_scale() const
{
    return m_scale;
}

double  GammaWalker::get_exponent() const
{
    return m_exponent;
}

void GammaWalker::set_scale(double scale)
{
    m_scale=scale;
}

void GammaWalker::set_exponent(double exponent)
{
    m_exponent=exponent;
}

void GammaWalker::move(int verbose)
{
    int dir=(int)(1-2*gsl_ran_bernoulli(m_rng,0.5));
    m_pos+=(double)(dir*gsl_ran_gamma(m_rng,m_exponent, m_scale));
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
//    py::class_<GammaWalker,ContinuousWalker>(
//            handle, "GammaWalker"
//            )
//        .def(py::init<>())
//        .def(py::init<double,double>())
//        .def(py::init<string,double,int,double,double>())
//        .def("move",
//                &GammaWalker::move,"a function that makes the walker perform a single step",py::arg("verbose")=0)
//        ;
//}
