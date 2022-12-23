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
        std::string m_potential_name; // name of potential
        double m_potential_parameter; // parameter of potential
        double (*m_potential)(int,double,double,double,double); // function pointer to potential function (more precisely it's derivative)
        // pointer material for lifetime generator
        std::string m_lifetime_name; 
        double m_lifetime_parameter; 
        double (*m_lifetime_generator)(gsl_rng*,double); // function pointer to potential function (more precisely it's derivative)

    public :

        //constructors --> only one here for now
        RTPpotentialWalker(std::string potential_name,double potential_paramer,std::string lifetime_name, double lifetime_parameter, double speed);

        //print functions
        void print_details() const;

        //setters and getters
        double  get_v() const;
        void  get_lifetime() const;

        void  get_potential() const;
        double  get_potential_parameter() const;

        double get_lifetime_parameter() const;
        void  get_lifetime_generator() const;

        void set_v(double v) ;

        void set_potential(std::string potential_name) ;
        void set_potential_parameter( double potential_paramer) ;

        void set_lifetime_parameter(double param);
        void set_lifetime_generator(std::string m_lifetime_name) ;

        //specific move function
        virtual void move(int verbose);

};

