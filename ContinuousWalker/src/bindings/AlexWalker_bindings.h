#pragma once

py::class_<AlexWalker,ContinuousWalker>(handle, "AlexWalker")

    .def(py::init<>(),"default constructor")


    .def(py::init<string,double,int>()
        ,py::arg("name")
        ,py::arg("position")
        ,py::arg("seed")
        ,"takes entry initial position(double), random seed(int))")

    .def("print_details"
        ,&AlexWalker::print_details
        ,py::call_guard<py::scoped_ostream_redirect>()//redirects cout to stdout in jupyter notebook
        ,"a function that prints details on the walker")

    .def("move",&AlexWalker::move,"a function that makes the walker perform a single step",py::arg("verbose")=0)
;
