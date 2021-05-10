#pragma once
#include <iostream>
#include "ContinuousWalker.h"

class LevyWalker : public ContinuousWalker
//should inherit most continuous walker methods
{
    protected :

        //we will use the standart GSL library and prepare for this
        double m_c,m_alpha;

    public :

        //constructors
        LevyWalker();
        LevyWalker(double c, double alpha);
        LevyWalker(std::string name, double pos, int seed, double c, double alpha);

        //print functions
        void print_details() const;

        //setters and getters
        double  get_alpha() const;
        double  get_c() const;

        void set_alpha(double alpha);
        void set_c(double c);

        //specific move function
        virtual void move(int verbose);

};

