#include <iostream>
#include <string>
#include <math.h>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>


using namespace std;

class DiscreteWalker
{
    //useful attributes for the walker
    private:

    string name;
    long m_pos;
    long m_lifetime;
    long m_min;
    long m_max;
    int m_seed; //each walker will have it's own seed

    public:

    void print_details(){

    }

    void move(){

    }

    bool isAlive(){
        return true;
    }

};

int main(){

    DiscreteWalker myWalker;
    myWalker.m_pos=10;
    myWalker.move();
    return 0;
}
