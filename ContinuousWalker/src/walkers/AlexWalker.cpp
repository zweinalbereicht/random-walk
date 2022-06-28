#include <iostream>
#include <string>
#include <math.h>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>
#include <pybind11/pybind11.h>
#include <stdlib.h>

#include "ContinuousWalker.h"
//le include precedent est il necessaire?
#include "AlexWalker.h"

using namespace std;
namespace py = pybind11;

AlexWalker::AlexWalker() : ContinuousWalker() 
{
    m_name="a simple alex walker";
}

AlexWalker::AlexWalker(string name, double pos, int seed) : ContinuousWalker(name, pos, seed) 
{
    m_name="a simple alex walker";
}

void AlexWalker::print_details() const
{
    ContinuousWalker::print_details();
}

void AlexWalker::move(int verbose)
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
