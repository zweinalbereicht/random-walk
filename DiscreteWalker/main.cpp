#include <iostream>
#include <string>
#include <math.h>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>
#include <time.h>

#include "DiscreteWalker.h"
using namespace std;

int main(){

    DiscreteWalker myWalker("happy walker", 2, time(NULL));

    //for(int j=0;j<10;j++){
    //    myWalker.print_details();
    //    myWalker.move();
    //}

    myWalker.print_details();
    myWalker.move_til_death();
    myWalker.print_details();

    return 0;
}
