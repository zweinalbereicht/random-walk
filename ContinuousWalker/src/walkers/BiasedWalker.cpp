#include <gsl/gsl_randist.h>
#include <gsl/gsl_rng.h>
#include <iostream>
#include <math.h>
#include <pybind11/pybind11.h>
#include <stdlib.h>
#include <string>

#include "ContinuousWalker.h"
#include "LevyWalker.h"
#include "BiasedWalker.h"
#include "AlexWalker.h"
#include "LaplaceWalker.h"

using namespace std;
namespace py = pybind11;

//Biased Gaussian
BiasedWalker::BiasedWalker() : ContinuousWalker() ,m_bias(0.0)
{}
void BiasedWalker::print_details() const
{
    ContinuousWalker::print_details();
    cout << "bias param : " << m_bias << endl;
}


double BiasedWalker::get_bias() const
{
    return m_bias;
}

void BiasedWalker::set_bias(const double bias)
{
    m_bias=bias;
}

void BiasedWalker::move(int verbose)
{
    m_pos+=m_bias;
    ContinuousWalker::move(verbose);
}

//Biased Levy
BiasedLevyWalker::BiasedLevyWalker() : LevyWalker() ,m_bias(0.0)
{}
void BiasedLevyWalker::print_details() const
{
    LevyWalker::print_details();
    cout << "bias param : " << m_bias << endl;
}


double BiasedLevyWalker::get_bias() const
{
    return m_bias;
}

void BiasedLevyWalker::set_bias(const double bias)
{
    m_bias=bias;
}

void BiasedLevyWalker::move(int verbose)
{
    m_pos+=m_bias;
    LevyWalker::move(verbose);
}

//Biased Alex
BiasedAlexWalker::BiasedAlexWalker() : AlexWalker() ,m_bias(0.0)
{}
void BiasedAlexWalker::print_details() const
{
    AlexWalker::print_details();
    cout << "bias param : " << m_bias << endl;
}


double BiasedAlexWalker::get_bias() const
{
    return m_bias;
}

void BiasedAlexWalker::set_bias(const double bias)
{
    m_bias=bias;
}

void BiasedAlexWalker::move(int verbose)
{
    m_pos+=m_bias;
    AlexWalker::move(verbose);
}

//Biased Laplace
BiasedLaplaceWalker::BiasedLaplaceWalker() : LaplaceWalker() ,m_bias(0.0)
{}
void BiasedLaplaceWalker::print_details() const
{
    LaplaceWalker::print_details();
    cout << "bias param : " << m_bias << endl;
}


double BiasedLaplaceWalker::get_bias() const
{
    return m_bias;
}

void BiasedLaplaceWalker::set_bias(const double bias)
{
    m_bias=bias;
}

void BiasedLaplaceWalker::move(int verbose)
{
    m_pos+=m_bias;
    LaplaceWalker::move(verbose);
}
