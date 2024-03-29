#include"Alex.h"
#include <fstream>
#include <gsl/gsl_randist.h>
#include <gsl/gsl_rng.h>
#include <iostream>
#include <limits>
#include <math.h>
#include <vector>

int main()
{

    int n=100000000;

    std::vector<double> results(n);

    gsl_rng *r = gsl_rng_alloc(gsl_rng_mt19937);
    for(int i=0;i<n;i++)
    {
        results[i]=gsl_ran_alex(r);
        //results[i]=gsl_ran_laplace(r, a);
    }

    gsl_rng_free(r);

    std::ofstream myfile;
    myfile.open("results.txt");
    for(int i=0;i<n;i++)
    {
        myfile << results[i] << "\n";
    }
    myfile.close();

    return 0;
}
