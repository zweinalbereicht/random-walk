#pragma once
#include <iostream>
#include "ContinuousWalker.h"

class GammaWalker : public ContinuousWalker
//should inherit most continuous walker methods
{
    protected :

        //we will use the standart GSL library and pass in the parameter as defined there
        double m_exponent; //the exponent of the monomial
        double m_scale; //scale in the exponential

    public :

        //constructors
        GammaWalker();
        GammaWalker(double scale,double exponent );
        GammaWalker(std::string name, double pos, int seed , double scale,double exponent);

        //print functions
        void print_details() const;

        //setters and getters
        double  get_scale() const;
        double  get_exponent() const;

        void set_scale(double scale);
        void set_exponent(double exponent);

        //specific move function
        virtual void move(int verbose);

};

