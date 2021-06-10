//#include <config.h>
#include <iostream>
#include <math.h>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>
#include <fstream>
#include <limits>
#include <vector>

#include "zipf.h"

int main()
{

    int n=3000000;

    std::vector<int> results(n);

    double a=1.3;
    gsl_rng *r = gsl_rng_alloc(gsl_rng_mt19937);
    int i=0;
    for(;i<n;i++)
    {
        results[i]=gsl_rng_zipf(r,a);
    }
    gsl_rng_free(r);


    std::ofstream myfile;
    myfile.open("results.txt");
    for(i=0;i<n;i++)
    {
        myfile << results[i] << "\n";
    }
    myfile.close();

}
