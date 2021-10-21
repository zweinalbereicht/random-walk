#pragma once
#include <iostream>
#include "ContinuousWalker.h"

class FWalker : public ContinuousWalker
//should inherit most continuous walker methods
{
    protected :

        //we will use the standart GSL library and pass in the parameter as defined there
        double m_nu1; //nu1 in F law
        double m_nu2; //the nu2 of the F law

    public :

        //constructors
        FWalker();
        FWalker(double nu1, double nu2);
        FWalker(std::string name, double pos, int seed ,double nu1, double nu2);

        //print functions
        void print_details() const;

        //setters and getters
        double  get_nu1() const;
        double  get_nu2() const;

        void set_nu1(double nu1);
        void set_nu2(double nu2);

        //specific move function
        virtual void move(int verbose);

};

