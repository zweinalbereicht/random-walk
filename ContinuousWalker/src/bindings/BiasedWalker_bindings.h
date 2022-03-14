#pragma once


py::class_<BiasedWalker,ContinuousWalker>(handle, "BiasedWalker")

    .def(py::init<>(),"default constructor")
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

    .def(py::init<>(),"default constructor")
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
