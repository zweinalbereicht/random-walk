#pragma once


py::class_<BiasedWalker,ContinuousWalker>(handle, "BiasedWalker")

    .def(py::init<>(),"creates a gaussianwalker with constant drift bias")
    .def("print_details"
        ,&BiasedWalker::print_details
        ,py::call_guard<py::scoped_ostream_redirect>()//redirects cout to stdout in jupyter notebook
        ,"a function that prints details on the walker")

    .def("get_bias",&BiasedWalker::get_bias,
            "a getter function for the  walker's bias")

    .def("set_bias",&BiasedWalker::set_bias
        ,py::arg("bias")
        ,"a setter function for the  walker's bias parameter")

    .def("move",&BiasedWalker::move,"a function that makes the walker perform a single step",py::arg("verbose")=0)
;

py::class_<BiasedLevyWalker,LevyWalker>(handle, "BiasedLevyWalker")

    .def(py::init<>(),"creates a levywalker with constant drift bias")
    .def("print_details"
        ,&BiasedLevyWalker::print_details
        ,py::call_guard<py::scoped_ostream_redirect>()//redirects cout to stdout in jupyter notebook
        ,"a function that prints details on the walker")

    .def("get_bias",&BiasedLevyWalker::get_bias,
            "a getter function for the  walker's bias")

    .def("set_bias",&BiasedLevyWalker::set_bias
        ,py::arg("bias")
        ,"a setter function for the  walker's bias parameter")

    .def("move",&BiasedLevyWalker::move,"a function that makes the walker perform a single step",py::arg("verbose")=0)
;

py::class_<BiasedAlexWalker,AlexWalker>(handle, "BiasedAlexWalker")

    .def(py::init<>(),"creates a levywalker with constant drift bias")
    .def("print_details"
        ,&BiasedAlexWalker::print_details
        ,py::call_guard<py::scoped_ostream_redirect>()//redirects cout to stdout in jupyter notebook
        ,"a function that prints details on the walker")

    .def("get_bias",&BiasedAlexWalker::get_bias,
            "a getter function for the  walker's bias")

    .def("set_bias",&BiasedAlexWalker::set_bias
        ,py::arg("bias")
        ,"a setter function for the  walker's bias parameter")

    .def("move",&BiasedAlexWalker::move,"a function that makes the walker perform a single step",py::arg("verbose")=0)
;

py::class_<BiasedLaplaceWalker,LaplaceWalker>(handle, "BiasedLaplaceWalker")

    .def(py::init<>(),"creates a levywalker with constant drift bias")
    .def("print_details"
        ,&BiasedLaplaceWalker::print_details
        ,py::call_guard<py::scoped_ostream_redirect>()//redirects cout to stdout in jupyter notebook
        ,"a function that prints details on the walker")

    .def("get_bias",&BiasedLaplaceWalker::get_bias,
            "a getter function for the  walker's bias")

    .def("set_bias",&BiasedLaplaceWalker::set_bias
        ,py::arg("bias")
        ,"a setter function for the  walker's bias parameter")

    .def("move",&BiasedLaplaceWalker::move,"a function that makes the walker perform a single step",py::arg("verbose")=0)
;
