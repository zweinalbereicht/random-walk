#pragma once


py::class_<ParetoWalker,ContinuousWalker>(handle, "ParetoWalker")

    .def(py::init<>(),"default constructor")

    .def(py::init<double,double>()
        ,py::arg("scale")
        ,py::arg("alpha")
        ,"takes entry scale(double) which is the corresponding scale, alpha(double) the levy exponent, which also corresponds to the the walk dimension")

    .def(py::init<string,double,int,double,double>()
        ,py::arg("name")
        ,py::arg("position")
        ,py::arg("seed")
        ,py::arg("c")
        ,py::arg("alpha")
        ,"takes entry initial position(double), random seed(int), c(double),alpha(double)")

    .def("print_details"
        ,&ParetoWalker::print_details
        ,py::call_guard<py::scoped_ostream_redirect>()//redirects cout to stdout in jupyter notebook
        ,"a function that prints details on the walker")

    .def("get_alpha",&ParetoWalker::get_alpha,
            "a getter function for the  walker's alpha")

    .def("get_c",&ParetoWalker::get_c,
            "a getter function for the  walker's c parameter")

    .def("set_alpha",&ParetoWalker::set_alpha,
            "a setter function for the  walker's alpha")

    .def("set_c",&ParetoWalker::set_c,
            "a setter function for the  walker's c parameter")

    .def("move",&ParetoWalker::move,"a function that makes the walker perform a single step",py::arg("verbose")=0)

;
