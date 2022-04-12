#include <iostream>
#include <string>
#include <math.h>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>
#include <pybind11/pybind11.h>
#include <stdlib.h>

#include "ContinuousWalker.h"
//le include precedent est il necessaire?
#include "ParetoWalker.h"

using namespace std;
namespace py = pybind11;

ParetoWalker::ParetoWalker() : ContinuousWalker() ,m_c(1.0) ,m_alpha(2.0)
{}

ParetoWalker::ParetoWalker(double c, double alpha) : ContinuousWalker() ,m_c(c) ,m_alpha(alpha)
{}

ParetoWalker::ParetoWalker(string name, double pos, int seed, double c, double alpha) : ContinuousWalker(name, pos, seed) ,m_c(c) ,m_alpha(alpha)
{}

void ParetoWalker::print_details() const
{
    ContinuousWalker::print_details();
    cout << "scale param : " << m_c << endl;
    cout << "alpha param : " << m_alpha << endl;
}

double  ParetoWalker::get_alpha() const
{
    return m_alpha;
}

double  ParetoWalker::get_c() const
{
    return m_c;
}

void ParetoWalker::set_alpha(double alpha)
{
    m_alpha=alpha;
}

void ParetoWalker::set_c(double c)
{
    m_c=c;
}

void ParetoWalker::move(int verbose)
{
    double direction = gsl_ran_bernoulli(m_rng,0.5);
    m_pos+=(2*direction-1)*gsl_ran_pareto(m_rng, m_alpha, m_c);
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
