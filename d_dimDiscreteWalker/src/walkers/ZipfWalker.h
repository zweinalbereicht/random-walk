#pragma once

#include <iostream>
#include "DiscreteWalker.h"
#include <pybind11/pybind11.h>

#include "Zipf.h"

class ZipfWalker : public DiscreteWalker
//should inherit most continuous walker methods
{
    protected :

        //we will use the standart GSL library and prepare for this
        double m_alpha;

    public :

        //constructors
        ZipfWalker();
        ZipfWalker(double alpha); // this one will be in 2d
        ZipfWalker(double alpha, int d);
        ZipfWalker(std::string name, int d, const pybind11::list &pos,double alpha,int seed);

        //print functions
        void print_details() const;

        //setters and getters
        double  get_alpha() const;

        void set_alpha(double alpha);

        //specific move function
        virtual void move(int verbose);

};

