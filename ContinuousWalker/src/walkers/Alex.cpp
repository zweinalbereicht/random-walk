//#include <config.h>
#include <gsl/gsl_randist.h>
#include <gsl/gsl_rng.h>
#include<iostream>
#include <limits>
#include <cmath>

#include "Alex.h"

double //que veux t-on vraiment renvoyer à la fin
gsl_ran_alex(const gsl_rng * r)
{
    double U=0.0;
    U=gsl_rng_uniform(r);
    return std::pow(std::tan(M_PI*U/2.0),2);
}
