#pragma once


py::class_<LevyWalker,ContinuousWalker>(handle, "LevyWalker")

    .def(py::init<>(),"default constructor")

    .def(py::init<double,double>()
        ,py::arg("c")
        ,py::arg("alpha")
        ,"takes entry c(double) which is the corresponding a_mu, alpha(double) the levy exponent, which also corresponds to the the walk dimension")

    .def(py::init<string,double,int,double,double>()
        ,py::arg("name")
        ,py::arg("position")
        ,py::arg("seed")
        ,py::arg("c")
        ,py::arg("alpha")
        ,"takes entry initial position(double), random seed(int), c(double),alpha(double)")

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
