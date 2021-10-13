#pragma once
#include <iostream>
#include "GaussianWalker.h"

class RTLWalker : public GaussianWalker
//should inherit most continuous walker methods
{
    protected :

        //we will use the standart GSL library and prepare for this
        double m_v; //speed of the particle
        double m_g; //length scale of the laplace distribution

    public :

        //constructors
        RTLWalker();
        RTLWalker(double g,double v);
        RTLWalker(std::string name, int d,const pybind11::list &pos, int seed ,double g,double v);

        //print functions
        void print_details() const;

        //setters and getters
        double  get_g() const;
        double  get_v() const;

        void set_g(double g);
        void set_v(double v);

        //specific move function
        virtual void move(int verbose);

};

