#pragma once


py::class_<LevyWalker,GaussianWalker>(handle, "LevyWalker")

    .def(py::init<>(),"default constructor")

    .def(py::init<double,double>()
        ,py::arg("c")
        ,py::arg("alpha")
        ,"takes entry c(double) which is the corresponding a_mu, alpha(double) the levy exponent, which also corresponds to the the walk dimension")

    .def(py::init<string,int,pybind11::list &,int,double,double>()
        ,py::arg("name")
        ,py::arg("dimension")
        ,py::arg("walker")
        ,py::arg("seed")
        ,py::arg("c")
        ,py::arg("alpha")
        ,"initlaisation follows bthe argument names")

    .def("print_details"
        ,&LevyWalker::print_details
        ,py::call_guard<py::scoped_ostream_redirect>()//redirects cout to stdout in jupyter notebook
        ,"a function that prints details on the walker")

    .def("get_alpha",&LevyWalker::get_alpha,
            "a getter function for the  walker's alpha")

    .def("get_c",&LevyWalker::get_c,
            "a getter function for the  walker's c parameter")

    .def("set_alpha",&LevyWalker::set_alpha,
            "a setter function for the  walker's alpha")

    .def("set_c",&LevyWalker::set_c,
            "a setter function for the  walker's c parameter")

    .def("move",&LevyWalker::move
        ,py::arg("verbose")=0
        ,"a function that makes the walker perform a single step")
;
