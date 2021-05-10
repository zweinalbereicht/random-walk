#pragma once
#include <iostream>
#include "ContinuousWalker.h"

class LaplaceWalker : public ContinuousWalker
//should inherit most continuous walker methods
{
    protected :

        //we will use the standart GSL library and prepare for this
        double m_a;

    public :

        //constructors
        LaplaceWalker();
        LaplaceWalker(double a);
        LaplaceWalker(std::string name, double pos, int seed ,double a);

        //print functions
        void print_details() const;

        //setters and getters
        double  get_a() const;

        void set_a(double a);

        //specific move function
        void move(int verbose);

};

