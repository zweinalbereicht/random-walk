#pragma once

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
