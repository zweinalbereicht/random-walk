#pragma once
#include <iostream>

#include "ContinuousWalker.h"

class UniformWalker : public ContinuousWalker
//should inherit most continuous walker methods
{
    protected :

        //we will use the standart GSL library and pass in the parameter as defined there
        double m_scale; //the length in whitch the absolute value of the jump distribution lives

    public :

        //constructors
        UniformWalker();
        UniformWalker(double scale);
        UniformWalker(std::string name, double pos, int seed ,double scale);

        //print functions
        void print_details() const;

        //setters and getters
        double  get_scale() const;

        void set_scale(const double scale);

        //specific move function
        virtual void move(int verbose);

};

