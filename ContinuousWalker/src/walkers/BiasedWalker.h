#pragma once
#include <iostream>

#include "ContinuousWalker.h"
#include "LevyWalker.h"

class BiasedWalker : public ContinuousWalker
//should inherit most continuous walker methods
{
    protected :
        //we will use the standart GSL library and pass in the parameter as defined there
        double m_bias; //the length in whitch the absolute value of the jump distribution lives
    public :
        //constructors
        BiasedWalker();
        //print functions
        void print_details() const;
        //setters and getters
        double  get_bias() const;
        void set_bias(const double bias);
        //specific move function
        virtual void move(int verbose);
};

class BiasedLevyWalker : public LevyWalker
//should inherit most continuous walker methods
{
    protected :
        //we will use the standart GSL library and pass in the parameter as defined there
        double m_bias; //the length in whitch the absolute value of the jump distribution lives
    public :
        //constructors
        BiasedLevyWalker();
        //print functions
        void print_details() const;
        //setters and getters
        double  get_bias() const;
        void set_bias(const double bias);
        //specific move function
        virtual void move(int verbose);
};

