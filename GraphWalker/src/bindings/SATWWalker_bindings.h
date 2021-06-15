#pragma once

py::class_<SATWWalker,DiscreteWalker>(handle, "SATWWalker")

.def(py::init<>(),"default constructor")

.def(py::init<double>()
        ,py::arg("beta")
        ,"takes entry beta(double)")

.def(py::init<string,long,int,double>()
        ,py::arg("name")
        ,py::arg("position")
        ,py::arg("seed")
        ,py::arg("beta")
        ,"takes entry initial position(long), random seed(int), beta(double)")

    .def("get_beta",&SATWWalker::get_beta
            ,"a getter function for the  walker's beta")

    .def("set_beta",&SATWWalker::set_beta
            ,py::arg("beta")
            ,"a setter function for the  walker's beta")

    .def("print_details",&SATWWalker::print_details
            ,"a function that prints details on the walker")

    .def("move",&SATWWalker::move
            ,py::call_guard<py::scoped_ostream_redirect>()
            ,py::arg("verbose")=0
            ,"a function that makes the walker perform a single step")
    ;

