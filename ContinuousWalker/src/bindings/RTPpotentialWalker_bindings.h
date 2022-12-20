#pragma once

py::class_<RTPpotentialWalker,ContinuousWalker>(handle, "RTPpotentialWalker")

    .def(py::init<>(),"default constructor")

    .def(py::init<double,double>(),"takes entry v(speed), g(tumble rate (s^-A))")

    .def(py::init<string,double,double,double>()
        ,"constructor function"
        ,py::arg("potential_name")
        ,py::arg("potential_parameter")
        ,py::arg("speed")
        ,py::arg("tumble_rate"))

    .def("print_details"
        ,&RTPpotentialWalker::print_details
        ,py::call_guard<py::scoped_ostream_redirect>()//redirects cout to stdout in jupyter notebook
        ,"a function that prints details on the walker")

    .def("get_v",&RTPpotentialWalker::get_v,
            "a getter function for the  walker's speed parameter")
    .def("get_g",&RTPpotentialWalker::get_g,
            "a getter function for the  walker's tumble rate parameter")
    .def("get_potential",&RTPpotentialWalker::get_potential,
            "a getter function for the  walker's potential")
    .def("get_potential_parameter",&RTPpotentialWalker::get_potential_parameter,
            "a getter function for the  walker's potential parameter")

    .def("set_v",&RTPpotentialWalker::set_v,
            "a setter function for the  walker's speed parameter")
    .def("set_g",&RTPpotentialWalker::set_g,
            "a setter function for the  walker's tumble rate parameter")
    .def("set_potential",&RTPpotentialWalker::set_potential,
            "a setter function for the  walker's potential")
    .def("set_potential_parameter",&RTPpotentialWalker::set_potential_parameter,
            "a setter function for the  walker's potential parameter")

    .def("move",&RTPpotentialWalker::move,"a function that makes the walker perform a single step",py::arg("verbose")=0)

;

