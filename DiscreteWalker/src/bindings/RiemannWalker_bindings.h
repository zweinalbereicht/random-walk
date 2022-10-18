#pragma once

py::class_<RiemannWalker,DiscreteWalker>(handle, "RiemannWalker")

.def(py::init<>(),"default constructor")

.def(py::init<double,double>()
        ,py::arg("c")
        ,py::arg("beta")
        ,"takes entry c(double) and alpha(double)")

.def(py::init<string,long,int,double,double>()
        ,py::arg("name")
        ,py::arg("position")
        ,py::arg("seed")
        ,py::arg("c")
        ,py::arg("alpha")
        ,"takes entry initial position(long), random seed(int), c(double), alpha(double)")

    .def("print_details",&RiemannWalker::print_details
            ,"a function that prints details on the walker")

    .def("get_c",&RiemannWalker::get_c
            ,"a getter function for the  walker's c param")

    .def("get_alpha",&RiemannWalker::get_alpha
            ,"a getter function for the  walker's alpha param")

    .def("set_c",&RiemannWalker::set_c
            ,py::arg("c")
            ,"a setter function for the  walker's c")

    .def("set_c_zipf",&RiemannWalker::set_c_zipf
            ,"setting the walker's scale to match the exact Zipf distribution")

    .def("set_alpha",&RiemannWalker::set_alpha
            ,py::arg("alpha")
            ,"a setter function for the  walker's alpha")

    .def("move",&RiemannWalker::move
            ,py::call_guard<py::scoped_ostream_redirect>()
            ,py::arg("verbose")=0
            ,"a function that makes the walker perform a single step")
    ;

