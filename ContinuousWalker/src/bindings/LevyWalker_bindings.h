#pragma once


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
