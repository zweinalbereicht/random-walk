#include <iostream>
#include <string>
#include <math.h>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>
#include <pybind11/pybind11.h>
#include <stdlib.h>

#include "DiscreteWalker.h"
//le include precedent est il necessaire?
#include "RiemannWalker.h"
//#include "Zipf.h"

using namespace std;
namespace py = pybind11;

RiemannWalker::RiemannWalker() : DiscreteWalker() ,m_c(1.0) ,m_alpha(2.0)
{}

RiemannWalker::RiemannWalker(double c, double alpha) : DiscreteWalker() ,m_c(c) ,m_alpha(alpha)
{}

RiemannWalker::RiemannWalker(string name, long pos, int seed, double c, double alpha) : DiscreteWalker(name, pos, seed) ,m_c(c) ,m_alpha(alpha)
{}

void RiemannWalker::print_details() const
{
    DiscreteWalker::print_details();
    cout << "c param : " << m_c << endl;
    cout << "alpha param : " << m_alpha << endl;
}

double  RiemannWalker::get_alpha() const
{
    return m_alpha;
}

double  RiemannWalker::get_c() const
{
    return m_c;
}

void RiemannWalker::set_alpha(double alpha)
{
    m_alpha=alpha;
}

void RiemannWalker::set_c(double c)
{
    m_c=c;
}

void RiemannWalker::move(int verbose)
{
    double m = gsl_ran_levy(m_rng, m_c, m_alpha);
    m_pos=round(m_pos+m);
    if(verbose)
        cout << "pos : " << m_pos << endl;
    //cout << "moving this move" << endl; //untick this if you want to make sure the right function is called
    if (m_pos>m_max){
        m_max=m_pos;
    }
    else if (m_pos<m_min){
        m_min=m_pos;
    }
    m_lifetime+=1;
}

