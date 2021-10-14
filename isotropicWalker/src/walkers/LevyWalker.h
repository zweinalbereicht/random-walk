#pragma once
#include <iostream>
#include "GaussianWalker.h"

class LevyWalker : public GaussianWalker
//should inherit most continuous walker methods
{
    protected :

        //we will use the standart GSL library and prepare for this
        // m_c is the scale (essentially tha a_mu) and m_alpha is the exponent
        double m_c,m_alpha;

    public :

        //constructors
        LevyWalker();
        LevyWalker(double c, double alpha);
        LevyWalker(std::string name, const int d,const pybind11::list &pos, const int seed, const double c, const double alpha);

        //print functions
        void print_details() const;

        //setters and getters
        double  get_alpha() const;
        double  get_c() const;

        void set_alpha(double alpha);
        void set_c(double c);

        //specific move function
        virtual void move(int verbose=0);

};

