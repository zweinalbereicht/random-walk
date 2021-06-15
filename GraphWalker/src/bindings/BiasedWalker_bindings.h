#pragma once

py::class_<BiasedWalker,DiscreteWalker>(handle, "BiasedWalker")

.def(py::init<>(),"default constructor")

.def(py::init<double>()
        ,py::arg("bias p")
        ,"takes entry p(double)")

.def(py::init<string,long,int,double>()
        ,        py::arg("name")
        ,py::arg("position p")
        ,py::arg("seed")
        ,py::arg("bias p")
        ,"takes entry initial position(long), random seed(int), p(double)")

    .def("print_details",&BiasedWalker::print_details
            ,"a function that prints details on the walker")

    .def("get_p",&BiasedWalker::get_p
            ,"a getter function for the  walker's p")

    .def("set_p",&BiasedWalker::set_p
            ,py::arg("bias p")
            ,"a setter function for the  walker's p")

    .def("move",&BiasedWalker::move
            ,py::call_guard<py::scoped_ostream_redirect>()
            ,py::arg("verbose")=0
            ,"a function that makes the walker perform a single step")
    ;
