#pragma once
#include <iostream>
#include "DiscreteWalker.h"

#include "Zipf.h"

class RiemannWalker : public DiscreteWalker
//should inherit most continuous walker methods
{
    protected :

        //we will use the standart GSL library and prepare for this
        double m_c,m_alpha;

    public :

        //constructors
        RiemannWalker();
        RiemannWalker(double c, double alpha);
        RiemannWalker(std::string name, long pos, int seed, double c, double alpha);

        //print functions
        void print_details() const;

        //setters and getters
        double  get_alpha() const;
        double  get_c() const;

        void set_alpha(double alpha);
        void set_c(double c);
        // the point of this one is to set c in order to mimick the zipf distribution tail wise
        void set_c_zipf();

        //specific move function
        virtual void move(int verbose);

};

