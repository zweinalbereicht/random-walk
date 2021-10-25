#include <iostream>
#include <string>
#include <math.h>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>
#include <pybind11/pybind11.h>
#include <stdlib.h>

#include "ContinuousWalker.h"
//le include precedent est il necessaire?
#include "FWalker.h"

using namespace std;
namespace py = pybind11;

FWalker::FWalker() : ContinuousWalker() ,m_nu1(1.0),m_nu2(2.0)
{}

FWalker::FWalker(double nu1,double nu2) : ContinuousWalker(),m_nu1(nu1),m_nu2(nu2)
{}

FWalker::FWalker(string name, double pos, int seed,double nu1, double nu2) : ContinuousWalker(name, pos, seed) ,m_nu1(nu1),m_nu2(nu2)
{}

void FWalker::print_details() const
{
    ContinuousWalker::print_details();
    cout << "nu1 param : " << m_nu1 << endl;
    cout << "nu2 param : " << m_nu2 << endl;
}


double  FWalker::get_nu1() const
{
    return m_nu1;
}

double  FWalker::get_nu2() const
{
    return m_nu2;
}

void FWalker::set_nu1(double nu1)
{
    m_nu1=nu1;
}

void FWalker::set_nu2(double nu2)
{
    m_nu2=nu2;
}

void FWalker::move(int verbose)
{
    int dir=(int)(1-2*gsl_ran_bernoulli(m_rng,0.5));
    m_pos+=(double)(dir*gsl_ran_alex(m_rng));
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
