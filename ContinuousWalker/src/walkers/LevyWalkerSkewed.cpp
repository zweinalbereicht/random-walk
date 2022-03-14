#include <iostream>
#include <string>
#include <math.h>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>
#include <pybind11/pybind11.h>
#include <stdlib.h>

#include "ContinuousWalker.h"
//le include precedent est il necessaire?
#include "LevyWalkerSkewed.h"

using namespace std;
namespace py = pybind11;

LevyWalkerSkewed::LevyWalkerSkewed() : ContinuousWalker() ,m_c(1.0) ,m_alpha(2.0), m_beta(0.0)
{}

LevyWalkerSkewed::LevyWalkerSkewed(double c, double alpha,double beta) : ContinuousWalker() ,m_c(c) ,m_alpha(alpha), m_beta(beta)
{}

LevyWalkerSkewed::LevyWalkerSkewed(string name, double pos, int seed, double c, double alpha, double beta) : ContinuousWalker(name, pos, seed) ,m_c(c) ,m_alpha(alpha)
{}

void LevyWalkerSkewed::print_details() const
{
    ContinuousWalker::print_details();
    cout << "c param : " << m_c << endl;
    cout << "alpha param : " << m_alpha << endl;
    cout << "beta param : " << m_beta << endl;
}

double  LevyWalkerSkewed::get_alpha() const
{
    return m_alpha;
}

double  LevyWalkerSkewed::get_c() const
{
    return m_c;
}

double  LevyWalkerSkewed::get_beta() const
{
    return m_beta;
}

void LevyWalkerSkewed::set_alpha(double alpha)
{
    m_alpha=alpha;
}

void LevyWalkerSkewed::set_c(double c)
{
    m_c=c;
}

void LevyWalkerSkewed::set_beta(double beta)
{
    m_beta=beta;
}

void LevyWalkerSkewed::move(int verbose)
{
    m_pos+=gsl_ran_levy_skew(m_rng, m_c, m_alpha,m_beta);
    m_lifetime+=1;
    if(verbose)
        cout << "pos : " << m_pos << endl;
    //cout << "moving this move" << endl; //untick this if you want to make sure the right function is called
    if (m_pos>m_max){
        m_max=m_pos;
    }
    else if (m_pos<m_min){
        m_min=m_pos;
    }
}


//PYBIND11_MODULE(module_ContinuousWalker,handle){
//    py::class_<LevyWalkerSkewed,ContinuousWalker>(
//            handle, "LevyWalkerSkewed"
//            )
//        .def(py::init<>())
//        .def(py::init<double,double>())
//        .def(py::init<string,double,int,double,double>())
//        .def("move",
//                &LevyWalkerSkewed::move,"a function that makes the walker perform a single step",py::arg("verbose")=0)
//        ;
//}
