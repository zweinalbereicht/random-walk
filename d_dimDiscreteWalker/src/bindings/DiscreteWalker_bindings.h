#pragma once


py::class_<DiscreteWalker>(handle, "DiscreteWalker")

.def(py::init<>(),"default constructor")

.def(py::init<string,int, std::vector<long>,int>()
        ,py::arg("name")
        ,py::arg("position")
        ,py::arg("seed"))

    .def("print_details",&DiscreteWalker::print_details
            ,py::call_guard<py::scoped_ostream_redirect>()//redirects cout to stdout in jupyter notebook
            ,"a function that prints details on the walker")

    .def("get_pos",&DiscreteWalker::get_pos
            ,"a getter function for the  walker's position")

    .def("get_max",&DiscreteWalker::get_max
            ,"a getter function for the  walker's maximum")

    .def("get_lifetime",&DiscreteWalker::get_lifetime
            ,"a getter function for the  walker's lifetime")

    .def("get_seed",&DiscreteWalker::get_seed
            ,"a getter function for the  walker's seed")

    .def("set_pos",&DiscreteWalker::set_pos
            ,py::arg("pos")
            ,"a setter function for the  walker's positonn")

    .def("set_max",&DiscreteWalker::set_max
            ,py::arg("max")
            ,"a setter function for the  walker's maximum")

    .def("set_lifetime",&DiscreteWalker::set_lifetime
            ,py::arg("lifetime")
            ,"a setter function for the  walker's lifetime")

    .def("set_seed",&DiscreteWalker::set_seed
            ,py::arg("seed")
            ,"a setter function for the  walker's seed")

    .def("move",&DiscreteWalker::move
            ,py::call_guard<py::scoped_ostream_redirect>()
            ,py::arg("verbose")=0
            ,"a function that makes the walker perform a single step, the default choice being any of the d_dimensional directions")

    .def("move_til_death",&DiscreteWalker::move_til_death
            ,py::call_guard<py::scoped_ostream_redirect>()
            ,py::arg("verbose")=0
            ,"a function that makes the walker walk until it reaches zero")

    .def("isAlive",&DiscreteWalker::isAlive
            ,"a function that says if the walker is still alive")

/*
    .def("move_til_death_bounded",&DiscreteWalker::move_til_death_bounded
            ,py::call_guard<py::scoped_ostream_redirect>()
            ,py::arg("N")
            ,py::arg("verbose")=0
            ,"a function that makes the walker walk on a ring of N sites until it reaches exactly zero")

    .def("move_fixed_max",&DiscreteWalker::move_fixed_max
            ,py::arg("maximum")
            ,"a function that makes the walker walk until death with two absorbing boundaries. If the function returns 0 than tha walker has exactly reached the fixed max value without bypassing it, 1 else.")

*/
    .def("move_fixed_time",&DiscreteWalker::move_fixed_time
            ,py::arg("time")
            ,"a function that makes the walker for a fixed time period. The function returns 0 if the walker died exactly on its nth step, 1 else.")

    /*
    .def("split_prob",&DiscreteWalker::split_prob
            ,py::arg("starting point s0")
            ,py::arg("left boundary s1")
            ,py::arg("right boundary s2")
            ,py::arg("n")
            ,"a function that returns the splitting probability to reach s2 before s1 starting from s0, averaged over n trials.")

    .def("max_prob",&DiscreteWalker::max_prob
            ,py::arg("starting point s0")
            ,py::arg("maximum s1")
            ,py::arg("n")
            ,"a function that returns the probability that the max is equal to s1, starting from s0, averaged over n trials.")
*/
    ;

