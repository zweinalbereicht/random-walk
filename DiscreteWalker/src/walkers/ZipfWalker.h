#pragma once

#include <iostream>
#include "DiscreteWalker.h"

#include "../../../custom_distributions/Zipf/Zipf.h"

class ZipfWalker : public DiscreteWalker
//should inherit most continuous walker methods
{
    protected :

        //we will use the standart GSL library and prepare for this
        double m_alpha;

    public :

        //constructors
        ZipfWalker();
        ZipfWalker(double alpha);
        ZipfWalker(std::string name, long pos, int seed,  double alpha);

        //print functions
        void print_details() const;

        //setters and getters
        double  get_alpha() const;

        void set_alpha(double alpha);

        //specific move function
        virtual void move(int verbose);

};

