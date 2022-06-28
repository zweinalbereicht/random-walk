#pragma once
#include <iostream>
#include "ContinuousWalker.h"
#include "Alex.h"

class AlexWalker : public ContinuousWalker
//should inherit most continuous walker methods
{
    protected :


    public :

        //constructors
        AlexWalker();
        AlexWalker(std::string name, double pos, int seed);

        //print functions
        void print_details() const;

        //specific move function
        virtual void move(int verbose);

};

