#pragma once


py::class_<LaplaceWalker,ContinuousWalker>(handle, "LaplaceWalker")

    .def(py::init<>(),"default constructor")

    .def(py::init<double>(),"takes entry a(double) the caracteristic jump length")

    .def(py::init<string,double,int,double>(),"takes entry initial position(double), random seed(int), a(double)")

    .def("print_details",&LaplaceWalker::print_details,
            "a function that prints details on the walker")

    .def("get_a",&LaplaceWalker::get_a,
            "a getter function for the  walker's a parameter")

    .def("set_a",&LaplaceWalker::set_a,
            "a setter function for the  walker's a parameter")

    .def("move",&LaplaceWalker::move,"a function that makes the walker perform a single step",py::arg("verbose")=0)

;

