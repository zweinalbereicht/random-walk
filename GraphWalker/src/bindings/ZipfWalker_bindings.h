#pragma once

py::class_<ZipfWalker,DiscreteWalker>(handle, "ZipfWalker")

.def(py::init<>()
        ,"default constructor")

.def(py::init<double>()
        ,py::arg("beta")
        ,"takes entry alpha(double)")

.def(py::init<string,long,int,double>()
        ,py::arg("name")
        ,py::arg("position")
        ,py::arg("seed")
        ,py::arg("alpha")
        ,"takes entry initial position(long), random seed(int),  alpha(double)")

    .def("print_details",&ZipfWalker::print_details
            ,"a function that prints details on the walker")

    .def("get_alpha",&ZipfWalker::get_alpha
            ,"a getter function for the  walker's alpha param")

    .def("set_alpha",&ZipfWalker::set_alpha
            ,py::arg("alpha")
            ,"a setter function for the  walker's alpha")

    .def("move",&ZipfWalker::move
            ,py::call_guard<py::scoped_ostream_redirect>()
            ,py::arg("verbose")=0
            ,"a function that makes the walker perform a single step")

    ;


