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

#include "Observables.h" //specific histogram creations

using namespace std;
namespace py = pybind11;

PYBIND11_MODULE(module_DiscreteWalker,handle){

    handle.doc()="this is our C++ module for discrete 1 dimensional walkers";

    py::class_<DiscreteWalker>(
                handle, "DiscreteWalker"
            )
            .def(py::init<>(),"default constructor")
            .def(py::init<string,long,int>(),
                    py::arg("name"),py::arg("position"), py::arg("seed"))

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
                    py::arg("pos"),
                    "a setter function for the  walker's positonn")

            .def("set_min",&DiscreteWalker::set_min,
                    py::arg("min"),
                    "a setter function for the  walker's minimum")

            .def("set_max",&DiscreteWalker::set_max,
                    py::arg("max"),
                    "a setter function for the  walker's maximum")

            .def("set_lifetime",&DiscreteWalker::set_lifetime,
                    py::arg("lifetime"),
                    "a setter function for the  walker's lifetime")

            .def("set_seed",&DiscreteWalker::set_seed,
                    py::arg("seed"),
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

            .def("move_til_death_bounded",&DiscreteWalker::move_til_death_bounded,
                    py::call_guard<py::scoped_ostream_redirect>(),
                    "a function that makes the walker walk on a ring of N sites until it reaches exactly zero",
                    py::arg("N"),py::arg("verbose")=0)

            .def("isAlive",&DiscreteWalker::isAlive,
                    "a function that says if the walker is still alive")

            .def("move_fixed_max",&DiscreteWalker::move_fixed_max,
                    py::arg("maximum"),
                    "a function that makes the walker walk until death with two absorbing boundaries. If the function returns 0 than tha walker has exactly reached the fixed max value without bypassing it, 1 else.")

            .def("move_fixed_time",&DiscreteWalker::move_fixed_time,
                    py::arg("time"),
                    "a function that makes the walker for a fixed time period. The function returns 0 if the walker died exactly on its nth step, 1 else.")

            .def("split_prob",&DiscreteWalker::split_prob,
                    py::arg("starting point s0"),py::arg("left boundary s1"),py::arg("right boundary s2"),py::arg("n"),
                    "a function that returns the splitting probability to reach s2 before s1 starting from s0, averaged over n trials.")

            .def("max_prob",&DiscreteWalker::max_prob,
                    py::arg("starting point s0"),py::arg("maximum s1"),py::arg("n"),
                    "a function that returns the probability that the max is equal to s1, starting from s0, averaged over n trials.")
            ;

    //Biased walker bindings
    py::class_<BiasedWalker,DiscreteWalker>(handle, "BiasedWalker")
        .def(py::init<>(),"default constructor")
        .def(py::init<double>(),
                py::arg("bias p"),
                "takes entry p(double)")
        .def(py::init<string,long,int,double>(),
                py::arg("name"),py::arg("position p"),py::arg("seed"),py::arg("bias p"),
                "takes entry initial position(long), random seed(int), p(double)")
        .def("print_details",&BiasedWalker::print_details,
                "a function that prints details on the walker")
        .def("get_p",&BiasedWalker::get_p,
                "a getter function for the  walker's p")
        .def("set_p",&BiasedWalker::set_p,
                py::arg("bias p"),
                "a setter function for the  walker's p")
        .def("move",&BiasedWalker::move,
                    py::call_guard<py::scoped_ostream_redirect>(),
                    "a function that makes the walker perform a single step",py::arg("verbose")=0)

        ;

    //SATW walker bindings
    py::class_<SATWWalker,DiscreteWalker>(handle, "SATWWalker")
        .def(py::init<>(),"default constructor")
        .def(py::init<double>(),
                py::arg("beta"),
                "takes entry beta(double)")
        .def(py::init<string,long,int,double>(),
                py::arg("name"),py::arg("position"),py::arg("seed"),py::arg("beta"),
                "takes entry initial position(long), random seed(int), beta(double)")
        .def("print_details",&SATWWalker::print_details,
                "a function that prints details on the walker")
        .def("get_beta",&SATWWalker::get_beta,
                "a getter function for the  walker's beta")
        .def("set_beta",&SATWWalker::set_beta,
                py::arg("beta"),
                "a setter function for the  walker's beta")
        .def("move",&SATWWalker::move,
                py::call_guard<py::scoped_ostream_redirect>(),
                "a function that makes the walker perform a single step",py::arg("verbose")=0)
        ;

    //Riemann walker bindings
    py::class_<RiemannWalker,DiscreteWalker>(handle, "RiemannWalker")
        .def(py::init<>(),"default constructor")
        .def(py::init<double,double>(),
                py::arg("c"),py::arg("beta"),
                "takes entry c(double) and alpha(double)")
        .def(py::init<string,long,int,double,double>(),
                py::arg("name"),py::arg("position"),py::arg("seed"),py::arg("c"),py::arg("alpha"),
                "takes entry initial position(long), random seed(int), c(double), alpha(double)")
        .def("print_details",&RiemannWalker::print_details,
                "a function that prints details on the walker")
        .def("get_c",&RiemannWalker::get_c,
                "a getter function for the  walker's c param")
        .def("get_alpha",&RiemannWalker::get_alpha,
                "a getter function for the  walker's alpha param")
        .def("set_c",&RiemannWalker::set_c,
                py::arg("c"),
                "a setter function for the  walker's c")
        .def("set_alpha",&RiemannWalker::set_alpha,
                py::arg("alpha"),
                "a setter function for the  walker's alpha")
        .def("move",&RiemannWalker::move,
                py::call_guard<py::scoped_ostream_redirect>(),
                "a function that makes the walker perform a single step",py::arg("verbose")=0)
        ;

    // these methods will be for very specific usecases, such as providing data for histograms for instance
    handle.def("first_test",&first_test);

}
