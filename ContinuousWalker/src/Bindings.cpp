#include <iostream>
#include <string>
#include <vector>
#include <pybind11/pybind11.h>
#include <stdlib.h>

#include "ContinuousWalker.h"
#include "LevyWalker.h"
#include "LaplaceWalker.h"
#include "GammaWalker.h"

using namespace std;
namespace py = pybind11;

PYBIND11_MODULE(module_ContinuousWalker,handle){

    handle.doc()="this is our C++ module for continuous 1 dimensional walkers";

    py::class_<ContinuousWalker>(
                handle, "ContinuousWalker"
            )
            .def(py::init<>(),"default constructor")
            .def(py::init<string,double,int>(),"takes entry name(string), position(double), random seed(int)")

            .def("print_details",&ContinuousWalker::print_details,
                    "a function that prints details on the walker")

            .def("get_pos",&ContinuousWalker::get_pos,
                    "a getter function for the  walker's position")

            .def("get_min",&ContinuousWalker::get_min,
                    "a getter function for the  walker's minimum")

            .def("get_max",&ContinuousWalker::get_max,
                    "a getter function for the  walker's maximum")

            .def("get_lifetime",&ContinuousWalker::get_lifetime,
                    "a getter function for the  walker's lifetime")

            .def("get_seed",&ContinuousWalker::get_seed,
                    "a getter function for the  walker's seed")

            .def("set_pos",&ContinuousWalker::set_pos,
                    "a setter function for the  walker's positonn")

            .def("set_min",&ContinuousWalker::set_min,
                    "a setter function for the  walker's minimum")

            .def("set_max",&ContinuousWalker::set_max,
                    "a setter function for the  walker's maximum")

            .def("set_lifetime",&ContinuousWalker::set_lifetime,
                    "a setter function for the  walker's lifetime")

            .def("set_seed",&ContinuousWalker::set_seed,
                    "a setter function for the  walker's seed")

            .def("move",
                    &ContinuousWalker::move,
                    "a function that makes the walker perform a single step, the default choice being a the normal distribution",
                    py::arg("verbose")=0)

            .def("move_til_death",&ContinuousWalker::move_til_death,
                    "a function that makes the walker walk until it reaches zero",
                    py::arg("verbose")=0)

            .def("isAlive",&ContinuousWalker::isAlive,
                    "a function that says if the walker is still alive")

            .def("move_fixed_max",&ContinuousWalker::move_fixed_max,
                    "a function that makes the walker walk until death with two absorbing boundaries. If the function returns 0 than tha walker has exactly reached the fixed max value without bypassing it, 1 else.")

            .def("move_fixed_time",&ContinuousWalker::move_fixed_time,
                    "a function that makes the walker for a fixed time period. The function returns 0 if the walker died exactly on its nth step, 1 else.")

            .def("split_prob",&ContinuousWalker::split_prob,
                    "args : (s0,s1,s2,n) -  a function that returns the splitting probability to reach s2 before s1 starting from s0, averaged over n trials.")
            ;

    //Levy walker bindings
    py::class_<LevyWalker,ContinuousWalker>(handle, "LevyWalker")
        .def(py::init<>(),"default constructor")
        .def(py::init<double,double>(),"takes entry c(double), alpha(double)")
        .def(py::init<string,double,int,double,double>(),"takes entry initial position(double), random seed(int), c(double),alpha(double)")
        .def("print_details",&LevyWalker::print_details,
                "a function that prints details on the walker")
        .def("get_alpha",&LevyWalker::get_alpha,
                "a getter function for the  walker's alpha")
        .def("get_c",&LevyWalker::get_c,
                "a getter function for the  walker's c parameter")
        .def("set_alpha",&LevyWalker::set_alpha,
                "a setter function for the  walker's alpha")
        .def("set_c",&LevyWalker::set_c,
                "a setter function for the  walker's c parameter")
        .def("move",&LevyWalker::move,"a function that makes the walker perform a single step",py::arg("verbose")=0)
        ;

    //Laplace walker bindings
    py::class_<LaplaceWalker,ContinuousWalker>(handle, "LaplaceWalker")
        .def(py::init<>(),"default constructor")
        .def(py::init<double>(),"takes entry a(double)")
        .def(py::init<string,double,int,double>(),"takes entry initial position(double), random seed(int), a(double)")
        .def("print_details",&LaplaceWalker::print_details,
                "a function that prints details on the walker")
        .def("get_a",&LaplaceWalker::get_a,
                "a getter function for the  walker's a parameter")
        .def("set_a",&LaplaceWalker::set_a,
                "a setter function for the  walker's a parameter")
        .def("move",&LaplaceWalker::move,"a function that makes the walker perform a single step",py::arg("verbose")=0)
        ;

    //Gamma walker bindings
    py::class_<GammaWalker,ContinuousWalker>(handle, "GammaWalker")
        .def(py::init<>(),"default constructor")
        .def(py::init<double,double>(),"takes entry scale(double), exponent(double) as defined in the GSL library")
        .def(py::init<string,double,int,double,double>(),"takes entry initial position(double), random seed(int), scale(double),exponent(double), as defined in the GSL library")
        .def("print_details",&GammaWalker::print_details,
                "a function that prints details on the walker")
        .def("get_scale",&GammaWalker::get_scale,
                "a getter function for the  walker's scale parameter")
        .def("get_exponent",&GammaWalker::get_exponent,
                "a getter function for the  walker's exponent parameter")
        .def("set_scale",&GammaWalker::set_scale,
                "a setter function for the  walker's scale parameter")
        .def("set_exponent",&GammaWalker::set_exponent,
                "a setter function for the  walker's exponent parameter")
        .def("move",&GammaWalker::move,"a function that makes the walker perform a single step",py::arg("verbose")=0)
        ;

}

