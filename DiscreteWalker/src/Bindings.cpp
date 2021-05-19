#include <pybind11/pybind11.h>
#include <pybind11/iostream.h>
#include <iostream>
#include <vector>
#include <string>
#include <stdlib.h>

#include "DiscreteWalker.h"
#include "BiasedWalker.h"
#include "SATWWalker.h"
#include "RiemannWalker.h"

using namespace std;
namespace py = pybind11;

PYBIND11_MODULE(module_DiscreteWalker,handle){

    handle.doc()="this is our C++ module for discrete 1 dimensional walkers";

    py::add_ostream_redirect(handle,"ostream_redirect");

    py::class_<DiscreteWalker>(
                handle, "DiscreteWalker"
            )
            .def(py::init<>(),"default constructor")
            .def(py::init<string,long,int>(),"takes entry name(string), position(long), random seed(int)")

            .def("print_details",&DiscreteWalker::print_details,
                    py::call_guard<py::scoped_ostream_redirect>(), //redirects cout to stdout in jupyter notebook
                    "a function that prints details on the walker")

            .def("get_pos",&DiscreteWalker::get_pos,
                    "a getter function for the  walker's position")

            .def("get_min",&DiscreteWalker::get_min,
                    "a getter function for the  walker's minimum")

            .def("get_max",&DiscreteWalker::get_max,
                    "a getter function for the  walker's maximum")

            .def("get_lifetime",&DiscreteWalker::get_lifetime,
                    "a getter function for the  walker's lifetime")

            .def("get_seed",&DiscreteWalker::get_seed,
                    "a getter function for the  walker's seed")

            .def("set_pos",&DiscreteWalker::set_pos,
                    "a setter function for the  walker's positonn")

            .def("set_min",&DiscreteWalker::set_min,
                    "a setter function for the  walker's minimum")

            .def("set_max",&DiscreteWalker::set_max,
                    "a setter function for the  walker's maximum")

            .def("set_lifetime",&DiscreteWalker::set_lifetime,
                    "a setter function for the  walker's lifetime")

            .def("set_seed",&DiscreteWalker::set_seed,
                    "a setter function for the  walker's seed")

            .def("move",
                    &DiscreteWalker::move,
                    py::call_guard<py::scoped_ostream_redirect>(),
                    "a function that makes the walker perform a single step, the default choice being up or down with prob 1/2",
                    py::arg("verbose")=0)

            .def("move_til_death",&DiscreteWalker::move_til_death,
                    py::call_guard<py::scoped_ostream_redirect>(),
                    "a function that makes the walker walk until it reaches zero",
                    py::arg("verbose")=0)

            .def("isAlive",&DiscreteWalker::isAlive,
                    "a function that says if the walker is still alive")

            .def("move_fixed_max",&DiscreteWalker::move_fixed_max,
                    "a function that makes the walker walk until death with two absorbing boundaries. If the function returns 0 than tha walker has exactly reached the fixed max value without bypassing it, 1 else.")

            .def("move_fixed_time",&DiscreteWalker::move_fixed_time,
                    "a function that makes the walker for a fixed time period. The function returns 0 if the walker died exactly on its nth step, 1 else.")

            .def("split_prob",&DiscreteWalker::split_prob,
                    "args : (s0,s1,s2,n) -  a function that returns the splitting probability to reach s2 before s1 starting from s0, averaged over n trials.")

            .def("max_prob",&DiscreteWalker::max_prob,
                    "args : (s0,s1,n) -  a function that returns the probability that the max is esual to s1, starting from s0, averaged over n trials.")
            ;

    //Biased walker bindings
    py::class_<BiasedWalker,DiscreteWalker>(handle, "BiasedWalker")
        .def(py::init<>(),"default constructor")
        .def(py::init<double>(),"takes entry p(double)")
        .def(py::init<string,long,int,double>(),"takes entry initial position(long), random seed(int), p(double)")
        .def("print_details",&BiasedWalker::print_details,
                "a function that prints details on the walker")
        .def("get_p",&BiasedWalker::get_p,
                "a getter function for the  walker's p")
        .def("set_p",&BiasedWalker::set_p,
                "a setter function for the  walker's p")
        .def("move",&BiasedWalker::move,
                    py::call_guard<py::scoped_ostream_redirect>(),
                    "a function that makes the walker perform a single step",py::arg("verbose")=0)

        ;

    //SATW walker bindings
    py::class_<SATWWalker,DiscreteWalker>(handle, "SATWWalker")
        .def(py::init<>(),"default constructor")
        .def(py::init<double>(),"takes entry beta(double)")
        .def(py::init<string,long,int,double>(),"takes entry initial position(long), random seed(int), beta(double)")
        .def("print_details",&SATWWalker::print_details,
                "a function that prints details on the walker")
        .def("get_beta",&SATWWalker::get_beta,
                "a getter function for the  walker's beta")
        .def("set_beta",&SATWWalker::set_beta,
                "a setter function for the  walker's beta")
        .def("move",&SATWWalker::move,
                py::call_guard<py::scoped_ostream_redirect>(),
                "a function that makes the walker perform a single step",py::arg("verbose")=0)
        ;

    //Riemann walker bindings
    py::class_<RiemannWalker,DiscreteWalker>(handle, "RiemannWalker")
        .def(py::init<>(),"default constructor")
        .def(py::init<double,double>(),"takes entry c(double) and alpha(double)")
        .def(py::init<string,long,int,double,double>(),"takes entry initial position(long), random seed(int), c(double), alpha(double)")
        .def("print_details",&RiemannWalker::print_details,
                "a function that prints details on the walker")
        .def("get_c",&RiemannWalker::get_c,
                "a getter function for the  walker's c param")
        .def("get_alpha",&RiemannWalker::get_alpha,
                "a getter function for the  walker's alpha param")
        .def("set_c",&RiemannWalker::set_c,
                "a setter function for the  walker's c")
        .def("set_alpha",&RiemannWalker::set_alpha,
                "a setter function for the  walker's alpha")
        .def("move",&RiemannWalker::move,
                py::call_guard<py::scoped_ostream_redirect>(),
                "a function that makes the walker perform a single step",py::arg("verbose")=0)
        ;


}
