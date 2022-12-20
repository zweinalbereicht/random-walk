#pragma once
#include <iostream>
#include <string_view>
#include "ContinuousWalker.h"

class RTPpotentialWalker : public ContinuousWalker
//should inherit most continuous walker methods
{
    protected :

        //we will use the standart GSL library and prepare for this
        double m_v; // speed
        double m_g; // tumble rate
        std::string m_potential_name; // name of potential
        double m_potential_parameter; // parameter of potential
        double (*m_potential)(int,double,double,double,double); // function pointer to potential function (more precisely it's derivative)

    public :

        //constructors
        RTPpotentialWalker();
        RTPpotentialWalker(double v,double g);
        RTPpotentialWalker(std::string potential_name,double potential_paramer,double v, double g);

        //print functions
        void print_details() const;

        //setters and getters
        double  get_v() const;
        double  get_g() const;
        void  get_potential() const;
        double  get_potential_parameter() const;

        void set_v(double v) ;
        void set_g(double g) ;
        void set_potential(std::string potential_name) ;
        void set_potential_parameter( double potential_paramer) ;

        //specific move function
        virtual void move(int verbose);

};

