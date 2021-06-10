#pragma once

//#include <config.h>
#include <math.h>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>
#include <limits>

unsigned int
gsl_ran_zipf(const gsl_rng * r, double a);
