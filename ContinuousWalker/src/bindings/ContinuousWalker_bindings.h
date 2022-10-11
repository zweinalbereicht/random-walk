#pragma once

py::class_<ContinuousWalker>(handle, "ContinuousWalker")

	.def(py::init<>(),"default constructor")

	.def(py::init<string,double,int>(),"takes entry name(string), position(double), random seed(int)")

	.def("print_details"
            ,&ContinuousWalker::print_details
            ,py::call_guard<py::scoped_ostream_redirect>()//redirects cout to stdout in jupyter notebook
            ,"a function that prints details on the walker")

	.def("get_pos",&ContinuousWalker::get_pos,
        "a getter function for the  walker's position")

	.def("get_min",&ContinuousWalker::get_min,
        "a getter function for the  walker's minimum")

	.def("get_max",&ContinuousWalker::get_max,
        "a getter function for the  walker's maximum")

	.def("get_lifetime",&ContinuousWalker::get_lifetime,
        "a getter function for the  walker's lifetime")

	.def("get_seed",&ContinuousWalker::get_seed,
        "a getter function for the  walker's seed")

	.def("set_pos",&ContinuousWalker::set_pos,
        "a setter function for the  walker's positonn")

	.def("set_min",&ContinuousWalker::set_min,
        "a setter function for the  walker's minimum")

	.def("set_max",&ContinuousWalker::set_max,
        "a setter function for the  walker's maximum")

	.def("set_lifetime",&ContinuousWalker::set_lifetime,
        "a setter function for the  walker's lifetime")

	.def("set_seed",&ContinuousWalker::set_seed,
        "a setter function for the  walker's seed")

	.def("move"
            ,&ContinuousWalker::move
            ,py::call_guard<py::scoped_ostream_redirect>()
            ,"a function that makes the walker perform a single step, the default choice being a the normal distribution"
            ,py::arg("verbose")=0)

	.def("move_bounded_crossing"
            ,&ContinuousWalker::move_bounded_crossing
            ,py::call_guard<py::scoped_ostream_redirect>()
            ,py::arg("size")=0
            ,py::arg("verbose")=0
            ,"a function that makes the walker perform a single step in the bounded crossing convention")

	.def("move_til_covered_crossing"
            ,&ContinuousWalker::move_til_covered_crossing
            ,py::call_guard<py::scoped_ostream_redirect>()
            ,py::arg("size")=0
            ,"a function that makes the walker move until the ring has been fully visited, with the crossing convention")

	.def("move_til_death"
            ,&ContinuousWalker::move_til_death
            ,py::call_guard<py::scoped_ostream_redirect>()
            ,"a function that makes the walker walk until it reaches zero"
            ,py::arg("verbose")=0)

	.def("isAlive",&ContinuousWalker::isAlive,
        "a function that says if the walker is still alive")

	.def("move_fixed_max",&ContinuousWalker::move_fixed_max,
        "a function that makes the walker walk until death with two absorbing boundaries. If the function returns 0 than the walker has exactly reached the fixed max value without bypassing it, 1 else.")

	.def("move_fixed_time",&ContinuousWalker::move_fixed_time,
        "a function that makes the walker for a fixed time period.")

	.def("move_fixed_time_record_territory",&ContinuousWalker::move_fixed_time_record_territory,"a function that makes the walker for a fixed time period and record the territory it has seen, with discretization step 1 (ie we are flooring the position).")

	.def("move_til_covered"
      ,&ContinuousWalker::move_til_covered
      ,"a function that makes the walker move until the underlying lattice is fully covered ")

	.def("move_bounded_fixed_time",&ContinuousWalker::move_bounded_fixed_time,
        "a function that makes the walker for a fixed time period on a ring.")

	.def("split_prob",&ContinuousWalker::split_prob,
        "args : (s0,s1,s2,n) -  a function that returns the splitting probability to reach s2 before s1 starting from s0, averaged over n trials.")
;
