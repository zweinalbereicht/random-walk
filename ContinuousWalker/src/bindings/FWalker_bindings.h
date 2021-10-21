#pragma once

py::class_<FWalker,ContinuousWalker>(handle, "FWalker")

    .def(py::init<>(),"default constructor")

    .def(py::init<double,double>()
        ,py::arg("nu1")
        ,py::arg("nu2")
        ,"takes entry nu1(double), nu2(double) as defined in the GSL library.")

    .def(py::init<string,double,int,double,double>()
        ,py::arg("name")
        ,py::arg("position")
        ,py::arg("seed")
        ,py::arg("nu1")
        ,py::arg("nu2")
        ,"takes entry initial position(double), random seed(int), nu1(double),nu2(double), as defined in the GSL library")

    .def("print_details"
        ,&FWalker::print_details
        ,py::call_guard<py::scoped_ostream_redirect>()//redirects cout to stdout in jupyter notebook
        ,"a function that prints details on the walker")

    .def("get_nu1",&FWalker::get_nu1,
            "a getter function for the  walker's nu1 parameter")

    .def("get_nu2",&FWalker::get_nu2,
            "a getter function for the  walker's nu2 parameter")

    .def("set_nu1",&FWalker::set_nu1,
            "a setter function for the  walker's nu1 parameter")

    .def("set_nu2",&FWalker::set_nu2,
            "a setter function for the  walker's nu2 parameter")

    .def("move",&FWalker::move,"a function that makes the walker perform a single step",py::arg("verbose")=0)
;
