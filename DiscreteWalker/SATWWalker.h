#pragma once
#include <iostream>
#include "DiscreteWalker.h"

class SATWWalker : public DiscreteWalker
//should inherit most continuous walker methods
{
    protected :

        //we will use the standart GSL library and prepare for this
        double m_beta; //rightward biased

    public :

        //constructors
        SATWWalker();
        SATWWalker(double beta);
        SATWWalker(std::string name, long pos, int seed ,double beta);

        //print functions
        void print_details() const;

        //setters and getters
        double  get_beta() const;

        void set_beta(double beta);

        //specific move function
        virtual void move(int verbose);

};

