#include <iostream>
#include <string>
#include <math.h>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>
#include <pybind11/pybind11.h>
#include <stdlib.h>

#include "ContinuousWalker.h"
//le include precedent est il necessaire?
#include "LaplaceWalker.h"

using namespace std;
namespace py = pybind11;

LaplaceWalker::LaplaceWalker() : ContinuousWalker() ,m_a(1.0)
{}

LaplaceWalker::LaplaceWalker(double a) : ContinuousWalker(),m_a(a)
{}

LaplaceWalker::LaplaceWalker(string name, double pos, int seed,double a) : ContinuousWalker(name, pos, seed) ,m_a(1.0)
{}

void LaplaceWalker::print_details() const
{
    ContinuousWalker::print_details();
    cout << "a param : " << m_a << endl;
}


double  LaplaceWalker::get_a() const
{
    return m_a;
}

void LaplaceWalker::set_a(double a)
{
    m_a=a;
}

void LaplaceWalker::move(int verbose)
{
    m_pos+=gsl_ran_laplace(m_rng, m_a);
    if(verbose)
        cout << "pos : " << m_pos << endl;
}


//PYBIND11_MODULE(module_ContinuousWalker,handle){
//    py::class_<LaplaceWalker,ContinuousWalker>(
//            handle, "LaplaceWalker"
//            )
//        .def(py::init<>())
//        .def(py::init<double,double>())
//        .def(py::init<string,double,int,double,double>())
//        .def("move",
//                &LaplaceWalker::move,"a function that makes the walker perform a single step",py::arg("verbose")=0)
//        ;
//}