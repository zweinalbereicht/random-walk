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

LevyWalker::LevyWalker() : ContinuousWalker() m_c(1.0) m_alpha(2.0)
{}

LevyWalker::LevyWalker(double c, double alpha) : ContinuousWalker() m_c(c) m_alpha(alpha)
{}

LevyWalker::LevyWalker(string name, double pos, int seed, double c, double alpha) : ContinuousWalker(name, pos, seed) m_c(1.0) m_alpha(2.0)
{}

void LevyWalker::move(int verbose)
{}
