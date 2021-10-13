#pragma once


py::class_<RTLWalker,GaussianWalker>(handle, "RTLWalker")

    .def(py::init<>(),"default constructor")

    .def(py::init<double,double>()
        ,py::arg("time scale")
        ,py::arg("speed"))

    .def(py::init<string,int,pybind11::list &,int,double,double>()
        ,py::arg("name")
        ,py::arg("dim")
        ,py::arg("position")
        ,py::arg("seed")
        ,py::arg("time scale")
        ,py::arg("speed"))

    .def("print_details"
        ,&RTLWalker::print_details
        ,py::call_guard<py::scoped_ostream_redirect>()//redirects cout to stdout in jupyter notebook
        ,"a function that prints details on the walker")

    .def("get_g",&RTLWalker::get_g,
            "a getter function for the  walker's time scale  parameter")

    .def("get_v",&RTLWalker::get_v,
            "a getter function for the  walker's speed parameter")

    .def("set_g",&RTLWalker::set_g,
            "a setter function for the  walker's time scale parameter")

    .def("set_v",&RTLWalker::set_v,
            "a setter function for the  walker's speed parameter")

    .def("move",&RTLWalker::move
        ,py::arg("verbose")=0
        ,"a function that makes the walker perform a single step")

;

