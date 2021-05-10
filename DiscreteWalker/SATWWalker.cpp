#include <iostream>
#include <string>
#include <math.h>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>
#include <pybind11/pybind11.h>
#include <stdlib.h>

#include "DiscreteWalker.h"
//le include precedent est il necessaire?
#include "SATWWalker.h"

using namespace std;
namespace py = pybind11;

SATWWalker::SATWWalker() : DiscreteWalker() ,m_beta(0.5)
{}

SATWWalker::SATWWalker(double beta) : DiscreteWalker(),m_beta(beta)
{}

SATWWalker::SATWWalker(string name, long pos, int seed,double beta) : DiscreteWalker(name, pos, seed) ,m_beta(beta)
{}

void SATWWalker::print_details() const
{
    DiscreteWalker::print_details();
    cout << "beta param : " << m_beta << endl;
}


double  SATWWalker::get_beta() const
{
    return m_beta;
}

void SATWWalker::set_beta(double beta)
{
    m_beta=beta;
}

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

//PYBIND11_MODULE(module_DiscreteWalker,handle){
//    py::class_<SATWWalker,DiscreteWalker>(
//            handle, "SATWWalker"
//            )
//        .def(py::init<>())
//        .def(py::init<double,double>())
//        .def(py::init<string,double,int,double,double>())
//        .def("move",
//                &SATWWalker::move,"a function that makes the walker perform a single step",py::arg("verbose")=0)
//        ;
//}
