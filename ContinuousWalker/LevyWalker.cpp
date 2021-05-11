#include <iostream>
#include <string>
#include <math.h>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>
#include <pybind11/pybind11.h>
#include <stdlib.h>

#include "ContinuousWalker.h"
//le include precedent est il necessaire?
#include "LevyWalker.h"

using namespace std;
namespace py = pybind11;

LevyWalker::LevyWalker() : ContinuousWalker() ,m_c(1.0) ,m_alpha(2.0)
{}

LevyWalker::LevyWalker(double c, double alpha) : ContinuousWalker() ,m_c(c) ,m_alpha(alpha)
{}

LevyWalker::LevyWalker(string name, double pos, int seed, double c, double alpha) : ContinuousWalker(name, pos, seed) ,m_c(c) ,m_alpha(alpha)
{}

void LevyWalker::print_details() const
{
    ContinuousWalker::print_details();
    cout << "c param : " << m_c << endl;
    cout << "alpha param : " << m_alpha << endl;
}

double  LevyWalker::get_alpha() const
{
    return m_alpha;
}

double  LevyWalker::get_c() const
{
    return m_c;
}

void LevyWalker::set_alpha(double alpha)
{
    m_alpha=alpha;
}

void LevyWalker::set_c(double c)
{
    m_c=c;
}

void LevyWalker::move(int verbose)
{
    m_pos+=gsl_ran_levy(m_rng, m_c, m_alpha);
    if(verbose)
        cout << "pos : " << m_pos << endl;
    //cout << "moving this move" << endl; untick this if you want to make sure the right function is called
    if (m_pos>m_max){
        m_max=m_pos;
    }
    else if (m_pos<m_min){
        m_min=m_pos;
    }
}


//PYBIND11_MODULE(module_ContinuousWalker,handle){
//    py::class_<LevyWalker,ContinuousWalker>(
//            handle, "LevyWalker"
//            )
//        .def(py::init<>())
//        .def(py::init<double,double>())
//        .def(py::init<string,double,int,double,double>())
//        .def("move",
//                &LevyWalker::move,"a function that makes the walker perform a single step",py::arg("verbose")=0)
//        ;
//}
