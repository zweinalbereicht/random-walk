#pragma once


py::class_<LevyWalkerSkewed,ContinuousWalker>(handle, "LevyWalkerSkewed")

    .def(py::init<>(),"default constructor")

    .def(py::init<double,double,double>()
        ,py::arg("c")
        ,py::arg("alpha")
        ,py::arg("beta")
        ,"takes entry c(double) which is the corresponding a_mu, alpha(double) the levy exponent, which also corresponds to the the walk dimension, and beta the skew parameter")

    .def(py::init<string,double,int,double,double,double>()
        ,py::arg("name")
        ,py::arg("position")
        ,py::arg("seed")
        ,py::arg("c")
        ,py::arg("alpha")
        ,py::arg("beta")
    ,"takes entry initial position(double), random seed(int), c(double),alpha(double), and the skew beta(double)")

    .def("print_details"
        ,&LevyWalkerSkewed::print_details
        ,py::call_guard<py::scoped_ostream_redirect>()//redirects cout to stdout in jupyter notebook
        ,"a function that prints details on the walker")

    .def("get_alpha",&LevyWalkerSkewed::get_alpha,
            "a getter function for the  walker's alpha")

    .def("get_c",&LevyWalkerSkewed::get_c,
            "a getter function for the  walker's c parameter")

    .def("get_beta",&LevyWalkerSkewed::get_beta,
            "a getter function for the  walker's beta parameter")

    .def("set_alpha",&LevyWalkerSkewed::set_alpha,
            "a setter function for the  walker's alpha")

    .def("set_c",&LevyWalkerSkewed::set_c,
            "a setter function for the  walker's c parameter")

    .def("set_beta",&LevyWalkerSkewed::set_beta,
            "a setter function for the  walker's beta parameter")

    .def("move",&LevyWalkerSkewed::move,"a function that makes the walker perform a single step",py::arg("verbose")=0)

;
