#pragma once
#include <iostream>
#include "ContinuousWalker.h"

class LevyWalkerSkewed : public ContinuousWalker
//should inherit most continuous walker methods
{
    protected :

        //we will use the standart GSL library and prepare for this
        double m_c,m_alpha,m_beta;

    public :

        //constructors
        LevyWalkerSkewed();
        LevyWalkerSkewed(double c, double alpha, double beta);
        LevyWalkerSkewed(std::string name, double pos, int seed, double c, double alpha,double beta);

        //print functions
        void print_details() const;

        //setters and getters
        double  get_alpha() const;
        double  get_c() const;
        double  get_beta() const;

        void set_alpha(double alpha);
        void set_c(double c);
        void set_beta(double beta);

        //specific move function
        virtual void move(int verbose);

};

