#pragma once

py::class_<DiscreteWalker_pcg>(
        handle, "DiscreteWalker_pcg"
        )
.def(py::init<>(),"default constructor")
.def(py::init<string,long,int>(),
        py::arg("name"),py::arg("position"), py::arg("seed"))

.def("print_details",&DiscreteWalker_pcg::print_details,
        py::call_guard<py::scoped_ostream_redirect>(), //redirects cout to stdout in jupyter notebook
        "a function that prints details on the walker")

.def("get_pos",&DiscreteWalker_pcg::get_pos,
        "a getter function for the  walker's position")

.def("get_min",&DiscreteWalker_pcg::get_min,
        "a getter function for the  walker's minimum")

.def("get_max",&DiscreteWalker_pcg::get_max,
        "a getter function for the  walker's maximum")

.def("get_lifetime",&DiscreteWalker_pcg::get_lifetime,
        "a getter function for the  walker's lifetime")

.def("get_seed",&DiscreteWalker_pcg::get_seed,
        "a getter function for the  walker's seed")

.def("set_pos",&DiscreteWalker_pcg::set_pos,
        py::arg("pos"),
        "a setter function for the  walker's positonn")

.def("set_random_pos",&DiscreteWalker_pcg::set_random_pos,
        py::arg("N"),
        "a setter function for the  walker's positioning it at random on a ring of size N, 0 non reachable")

.def("set_min",&DiscreteWalker_pcg::set_min,
        py::arg("min"),
        "a setter function for the  walker's minimum")

.def("set_max",&DiscreteWalker_pcg::set_max,
        py::arg("max"),
        "a setter function for the  walker's maximum")

.def("set_lifetime",&DiscreteWalker_pcg::set_lifetime,
        py::arg("lifetime"),
        "a setter function for the  walker's lifetime")

.def("set_seed",&DiscreteWalker_pcg::set_seed,
        py::arg("seed"),
        "a setter function for the  walker's seed")

.def("move",
        &DiscreteWalker_pcg::move,
        py::call_guard<py::scoped_ostream_redirect>(),
        "a function that makes the walker perform a single step, the default choice being up or down with prob 1/2",
        py::arg("verbose")=0)

.def("move_til_death",&DiscreteWalker_pcg::move_til_death,
        py::call_guard<py::scoped_ostream_redirect>(),
        "a function that makes the walker walk until it reaches zero",
        py::arg("verbose")=0)

.def("move_til_death_bounded",&DiscreteWalker_pcg::move_til_death_bounded,
        py::call_guard<py::scoped_ostream_redirect>(),
        "a function that makes the walker walk on a ring of N sites until it reaches exactly zero",
        py::arg("N"),py::arg("verbose")=0)

.def("isAlive",&DiscreteWalker_pcg::isAlive,
        "a function that says if the walker is still alive")

.def("move_fixed_max",&DiscreteWalker_pcg::move_fixed_max,
        py::arg("maximum"),
        "a function that makes the walker walk until death with two absorbing boundaries. If the function returns 0 than tha walker has exactly reached the fixed max value without bypassing it, 1 else.")

.def("move_fixed_time",&DiscreteWalker_pcg::move_fixed_time,
        py::arg("time"),
        "a function that makes the walker for a fixed time period. The function returns 0 if the walker died exactly on its nth step, 1 else.")

.def("split_prob",&DiscreteWalker_pcg::split_prob,
        py::arg("starting point s0"),py::arg("left boundary s1"),py::arg("right boundary s2"),py::arg("n"),
        "a function that returns the splitting probability to reach s2 before s1 starting from s0, averaged over n trials.")

.def("max_prob",&DiscreteWalker_pcg::max_prob,
        py::arg("starting point s0"),py::arg("maximum s1"),py::arg("n"),
        "a function that returns the probability that the max is equal to s1, starting from s0, averaged over n trials.")
;
