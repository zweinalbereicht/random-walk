#include <iostream>
#include <string>
#include <math.h>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>
#include <pybind11/pybind11.h>
#include <stdlib.h>

#include "GaussianWalker.h"
//le include precedent est il necessaire?
#include "LevyWalker.h"

using namespace std;
namespace py = pybind11;

LevyWalker::LevyWalker() : GaussianWalker() ,m_c(1.0) ,m_alpha(2.0) // by default looks like a jump process pertaining to the Brownian basin
{
    m_name="A simple Levy walker";
}

LevyWalker::LevyWalker(double c, double alpha) : GaussianWalker() ,m_c(c) ,m_alpha(alpha)
{
    m_name="A simple Levy walker";
}

LevyWalker::LevyWalker(string name, const int d,const pybind11::list &pos, int seed, double c, double alpha) : GaussianWalker(name, d,pos, seed) ,m_c(c) ,m_alpha(alpha)
{
    m_name="A simple Levy walker";
}

void LevyWalker::print_details() const
{
    GaussianWalker::print_details();
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
    sphere_direction(m_d,m_direction,m_rng);
    double jump_length=gsl_ran_levy(m_rng, m_c, m_alpha);
    for(int i=0;i<m_d;i++){
        m_pos[i]+=jump_length*m_direction[i]; // move according to the jump drawn
    }
    m_lifetime+=1;
    double dist=euclidian_distance(m_pos);
    if(dist>m_max){
        m_max=dist;
    }

    if(verbose==1){
        cout << "coordinates : ( " ;
        for(int i=0;i<m_d;i++)
            cout << m_pos[i] << " ";
        cout << ")" <<endl;
    }
}


//PYBIND11_MODULE(module_GaussianWalker,handle){
//    py::class_<LevyWalker,GaussianWalker>(
//            handle, "LevyWalker"
//            )
//        .def(py::init<>())
//        .def(py::init<double,double>())
//        .def(py::init<string,double,int,double,double>())
//        .def("move",
//                &LevyWalker::move,"a function that makes the walker perform a single step",py::arg("verbose")=0)
//        ;
//}
