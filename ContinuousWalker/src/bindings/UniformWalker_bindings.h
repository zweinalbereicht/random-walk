#pragma once

py::class_<UniformWalker,ContinuousWalker>(handle, "UniformWalker")

    .def(py::init<>(),"default constructor")

    .def(py::init<double>()
            ,"takes entry scale(double), which represents the size of the interval the absolute jump value is taken in. For instance, scale=1.0 means the walker makes an overall jump in the [-1,1] interval.")

    .def(py::init<string,double,int,double>()
            ,"takes entry initial position(double), random seed(int), scale(double), as defined in the GSL library")

    .def("print_details"
        ,&UniformWalker::print_details
        ,py::call_guard<py::scoped_ostream_redirect>()//redirects cout to stdout in jupyter notebook
        ,"a function that prints details on the walker")

    .def("get_scale",&UniformWalker::get_scale,
            "a getter function for the  walker's scale parameter")

    .def("set_scale",&UniformWalker::set_scale,
            "a setter function for the  walker's scale parameter")

    .def("move",&UniformWalker::move,"a function that makes the walker perform a single step"
        ,py::arg("verbose")=0)
;
