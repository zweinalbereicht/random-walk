#pragma once

py::class_<RTPpotentialWalker,ContinuousWalker>(handle, "RTPpotentialWalker")

    .def(py::init<string,double,string,double,double>()
        ,"constructor function"
        ,py::arg("potential_name")
        ,py::arg("potential_parameter")
        ,py::arg("lifetime_name")
        ,py::arg("lifetime_parameter")
        ,py::arg("speed"))

    .def("print_details"
        ,&RTPpotentialWalker::print_details
        ,py::call_guard<py::scoped_ostream_redirect>()//redirects cout to stdout in jupyter notebook
        ,"a function that prints details on the walker")

    .def("get_v",&RTPpotentialWalker::get_v,
            "a getter function for the  walker's speed parameter")
    .def("get_potential",&RTPpotentialWalker::get_potential,
            "a getter function for the  walker's potential")
    .def("get_potential_parameter",&RTPpotentialWalker::get_potential_parameter,
            "a getter function for the  walker's potential parameter")
    .def("get_lifetime_generator",&RTPpotentialWalker::get_lifetime_generator,
            "a getter function for the  walker's lifetime generator")
    .def("get_lifetime_parameter",&RTPpotentialWalker::get_lifetime_parameter,
            "a getter function for the  walker's lifetime parameter")

    .def("set_v",&RTPpotentialWalker::set_v,
            "a setter function for the  walker's speed parameter")
    .def("set_potential",&RTPpotentialWalker::set_potential,
            "a setter function for the  walker's potential")
    .def("set_potential_parameter",&RTPpotentialWalker::set_potential_parameter,
            "a setter function for the  walker's potential parameter")
    .def("set_lifetime_generator",&RTPpotentialWalker::set_lifetime_generator,
            "a setter function for the  walker's lifetime generator")
    .def("set_lifetime_parameter",&RTPpotentialWalker::set_lifetime_parameter,
            "a setter function for the  walker's lifetime parameter")

    .def("move",&RTPpotentialWalker::move,"a function that makes the walker perform a single step",py::arg("verbose")=0)

;

