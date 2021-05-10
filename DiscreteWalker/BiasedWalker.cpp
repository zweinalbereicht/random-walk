#include <iostream>
#include <string>
#include <math.h>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>
#include <pybind11/pybind11.h>
#include <stdlib.h>

#include "DiscreteWalker.h"
//le include precedent est il necessaire?
#include "BiasedWalker.h"

using namespace std;
namespace py = pybind11;

BiasedWalker::BiasedWalker() : DiscreteWalker() ,m_p(0.5)
{}

BiasedWalker::BiasedWalker(double p) : DiscreteWalker(),m_p(p)
{}

BiasedWalker::BiasedWalker(string name, long pos, int seed,double p) : DiscreteWalker(name, pos, seed) ,m_p(p)
{}

void BiasedWalker::print_details() const
{
    DiscreteWalker::print_details();
    cout << "p param : " << m_p << endl;
}


double  BiasedWalker::get_p() const
{
    return m_p;
}

void BiasedWalker::set_p(double p)
{
    m_p=p;
}

void BiasedWalker::move(int verbose)
{
    int m = gsl_ran_bernoulli(m_rng, 1-m_p);
    m_pos+=(int) 1-2*m; //attention au sens ici
    if(verbose)
        cout << "pos : " << m_pos << endl;
    //cout << "in here" << endl;
    if (m_pos>m_max){
        m_max=m_pos;
    }
    else if (m_pos<m_min){
        m_min=m_pos;
    }
}

//PYBIND11_MODULE(module_DiscreteWalker,handle){
//    py::class_<BiasedWalker,DiscreteWalker>(
//            handle, "BiasedWalker"
//            )
//        .def(py::init<>())
//        .def(py::init<double,double>())
//        .def(py::init<string,double,int,double,double>())
//        .def("move",
//                &BiasedWalker::move,"a function that makes the walker perform a single step",py::arg("verbose")=0)
//        ;
//}
