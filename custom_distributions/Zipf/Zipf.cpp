//#include <config.h>
#include <gsl/gsl_randist.h>
#include <gsl/gsl_rng.h>
#include<iostream>
#include <limits>
#include <math.h>

#include "Zipf.h"

unsigned int //que veux t-on vraiment renvoyer à la fin?
gsl_ran_zipf(const gsl_rng * r, double a)
{

    double am1, b;

    am1 = a - 1.0;
    b = pow(2.0, am1);
    while (1) {

        double T, U, V, X;

        U = 1.0 - gsl_rng_uniform(r);
        V = gsl_rng_uniform(r);
        X = floor(pow(U, -1.0 / am1));
        /*
         * The real result may be above what can be represented in a signed
         * long. Since this is a straightforward rejection algorithm, we can
         * just reject this value. This function then models a Zipf
         * distribution truncated to sys.maxint.num --> on voudrait plutot des longs nous...
         */
        if (X > (double)std::numeric_limits<unsigned int>::max() || X < 1.0) {
            continue; //on saute l'etape suivante ici
        }

        T = pow(1.0 + 1.0 / X, am1);
        if (V * X * (T - 1.0) / (b - 1.0) <= T / b) {
            return (unsigned int )X; //petit cast à la fin
        }
    }
}
