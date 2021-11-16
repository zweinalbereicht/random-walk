#pragma once

py::class_<ContinuousAdaptativeWalker>(handle, "ContinuousAdaptativeWalker")

	.def(py::init<>(),"default constructor")

	.def(py::init<string,double,double,int>()
        ,py::arg("name")        
        ,py::arg("position")
        ,py::arg("diffusive coefficient")
        ,py::arg("seed"))

	.def("print_details"
            ,&ContinuousAdaptativeWalker::print_details
            ,py::call_guard<py::scoped_ostream_redirect>()//redirects cout to stdout in jupyter notebook
            ,"a function that prints details on the walker")

	.def("get_pos",&ContinuousAdaptativeWalker::get_pos,
        "a getter function for the  walker's position")

	.def("get_D",&ContinuousAdaptativeWalker::get_D,
        "a getter function for the  walker's dition")

	.def("get_min",&ContinuousAdaptativeWalker::get_min,
        "a getter function for the  walker's minimum")

	.def("get_max",&ContinuousAdaptativeWalker::get_max,
        "a getter function for the  walker's maximum")

	.def("get_lifetime",&ContinuousAdaptativeWalker::get_lifetime,
        "a getter function for the  walker's lifetime")

	.def("get_seed",&ContinuousAdaptativeWalker::get_seed,
        "a getter function for the  walker's seed")

	.def("set_pos",&ContinuousAdaptativeWalker::set_pos,
        "a setter function for the  walker's positonn")

	.def("set_D",&ContinuousAdaptativeWalker::set_D,
        "a setter function for the  walker's D")

	.def("set_min",&ContinuousAdaptativeWalker::set_min,
        "a setter function for the  walker's minimum")

	.def("set_max",&ContinuousAdaptativeWalker::set_max,
        "a setter function for the  walker's maximum")

	.def("set_lifetime",&ContinuousAdaptativeWalker::set_lifetime,
        "a setter function for the  walker's lifetime")

	.def("set_seed",&ContinuousAdaptativeWalker::set_seed,
        "a setter function for the  walker's seed")

	.def("move"
            ,&ContinuousAdaptativeWalker::move
            ,py::call_guard<py::scoped_ostream_redirect>()
            ,"a function that makes the walker perform a single step, the default choice being a the normal distribution"
            ,py::arg("verbose")=0)

	.def("move_til_death"
            ,&ContinuousAdaptativeWalker::move_til_death
            ,py::call_guard<py::scoped_ostream_redirect>()
            ,"a function that makes the walker walk until it reaches zero"
            ,py::arg("verbose")=0)

	.def("isAlive",&ContinuousAdaptativeWalker::isAlive,
        "a function that says if the walker is still alive")

	.def("move_fixed_max",&ContinuousAdaptativeWalker::move_fixed_max,
        "a function that makes the walker walk until death with two absorbing boundaries. If the function returns 0 than tha walker has exactly reached the fixed max value without bypassing it, 1 else.")

	.def("move_fixed_time",&ContinuousAdaptativeWalker::move_fixed_time,
        "a function that makes the walker for a fixed time period.")

	.def("split_prob",&ContinuousAdaptativeWalker::split_prob,
        "args : (s0,s1,s2,n) -  a function that returns the splitting probability to reach s2 before s1 starting from s0, averaged over n trials.")
;
