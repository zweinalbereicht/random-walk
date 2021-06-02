#pragma once
#include <iostream>

#include "DiscreteWalker.h"

class BiasedWalker : public DiscreteWalker
//should inherit most continuous walker methods
{
    protected :

        //we will use the standart GSL library and prepare for this
        double m_p; //rightward biased

    public :

        //constructors
        BiasedWalker();
        BiasedWalker(double p);
        BiasedWalker(std::string name, long pos, int seed ,double p);

        //print functions
        void print_details() const;

        //setters and getters
        double  get_p() const;

        void set_p(double p);

        //specific move function
        virtual void move(int verbose);

};

