#pragma once

//#include <config.h>
#include <gsl/gsl_randist.h>
#include <gsl/gsl_rng.h>
#include <limits>
#include <math.h>

unsigned int
gsl_ran_zipf(const gsl_rng * r, double a);
