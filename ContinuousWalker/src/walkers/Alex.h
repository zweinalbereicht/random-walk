#pragma once

//#include <config.h>
#include <gsl/gsl_randist.h>
#include <gsl/gsl_rng.h>
#include <limits>
#include <math.h>

// this distribution is a hand implementation of a special form of the Fdistribution in the GSL library
double
gsl_ran_alex(const gsl_rng * r);
