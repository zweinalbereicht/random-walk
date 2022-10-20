#pragma once

handle.def("splitting_probability"
        ,&splitting_probability
        ,py::arg("x0")
        ,py::arg("x")
        ,py::arg("walker")
        ,py::arg("N")
        ,"returns the splitting probability to reach x before zero (crossing convention), averaged over N trials.");

handle.def("splitting_probability_escaping_boundaries"
        ,&splitting_probability_escaping_boundaries
        ,py::arg("x0")
        ,py::arg("x")
        ,py::arg("vleft")
        ,py::arg("vright")
        ,py::arg("walker")
        ,py::arg("N")
        ,"returns the splitting probability to reach the rightmost boundary before the leftmost one. At each time step the rightboundary moves by a quantity vright (positive vright makes the boundary go rightwards) and the leftward_boundary moves by a quantity vleft (same convention). The results are averaged over N trials.");

handle.def("survival_probability"
        ,&survival_probability
        ,py::arg("x0")
        ,py::arg("n")
        ,py::arg("walker")
        ,py::arg("N")
        ,"returns the survival probability after n steps, (crossing convention), averaged over N trials.");

handle.def("strip_probability"
        ,&strip_probability
        ,py::arg("x")
        ,py::arg("walker")
        ,py::arg("nbSteps")
        ,py::arg("nbSimus")
        ,"returns the probability to observe a nbSteps long strip trajectory, whose max is greater than x, starting from 0.");

handle.def("survival_probability_bounded"
        ,&survival_probability_bounded
        ,py::arg("x0")
        ,py::arg("x")
        ,py::arg("n")
        ,py::arg("walker")
        ,py::arg("N")
        ,"returns the survival probability after n steps, (crossing convention), in the interval [0,x],averaged over N trials.");

handle.def("conditional_fpt_distribution"
        ,&conditional_fpt_distribution
        ,py::arg("x0")
        ,py::arg("x")
        ,py::arg("walker")
        ,py::arg("N")
        ,py::arg("target")=0
        ,"returns N condtional times through 0 if target = 0, or through x if target = 1. the walker starts from x0");

handle.def("conditional_fpt_mean"
        ,&conditional_fpt_mean
        ,py::arg("x0")
        ,py::arg("x")
        ,py::arg("walker")
        ,py::arg("N")
        ,py::arg("target")=0
        ,"returns the mean conditional first passage time through 0 if target = 0, or through x if target = 1, averaged over N trials. the walker starts from x0");

handle.def("fpt_probability"
        ,&fpt_probability
        ,py::arg("x0")
        ,py::arg("walker")
        ,py::arg("n")
        ,py::arg("N")
        ,"returns the probability to escape through 0 time n exactly, averaged over N trials. the walker starts from x0");

handle.def("conditional_fpt_probability"
        ,&conditional_fpt_probability
        ,py::arg("x0")
        ,py::arg("x")
        ,py::arg("walker")
        ,py::arg("n")
        ,py::arg("N")
        ,py::arg("target")=0
        ,"returns the probability to escape through 0 if target = 0, or through x if target = 1, at time n exactly, averaged over N trials. the walker starts from x0");

handle.def("unconditional_fpt_probability"
        ,&unconditional_fpt_probability
        ,py::arg("x0")
        ,py::arg("x")
        ,py::arg("walker")
        ,py::arg("n")
        ,py::arg("N")
        ,"returns the probability to escape the interval at time n exactly, averaged over N trials. the walker starts from x0");

handle.def("max_on_last_step_distribution"
        ,&max_on_last_step_distribution
        ,py::arg("x0 : initial position")
        ,py::arg("walker : our walker")
        ,py::arg("n : nb of steps the walker takes")
        ,py::arg("N : number of maximums for our statistics")
        ,py::arg("bounded_below")=0
        ,"returns N maxes attaigned exactly on the nth step, which is the last one. The walker startes from x0. If bounded_below is activated, the walker cannot go below 0.");

handle.def("time_conditioned_max_before_exit_distribution"
        ,&time_conditioned_max_before_exit_distribution
        ,py::arg("x0 : initial position")
        ,py::arg("walker : our walker")
        ,py::arg("n : step at which the max is reached")
        ,py::arg("N : number of maximums for our statistics")
        ,"returns N maxes attaigned exactly on the nth step,before the first exit time. The walker startes from x0.");

handle.def("time_conditioned_max_distribution"
        ,&time_conditioned_max_distribution
        ,py::arg("x0 : initial position")
        ,py::arg("walker : our walker")
        ,py::arg("n : step at which the max is reached")
        ,py::arg("nMax : total number of steps")
        ,py::arg("N : number of maximums for our statistics")
        ,"returns N maxes attaigned exactly on the nth step, in a trajectory of nMax steps. The walker startes from x0.");

handle.def("condtiional_position_distribution"
        ,&condtiional_position_distribution
        ,py::arg("x0 : initial position")
        ,py::arg("walker : our walker")
        ,py::arg("nbSteps :number of steps at which the propagator is evaluated")
        ,py::arg("nbSimus :number of positions for our statistics.")
        ,py::arg("x : rightward boundary")=0
        ,"returns nbSimus positions attaigned exactly on the nth step, in a semi infinite or bounded trajectory. The walker startes from x0.");

handle.def("territory_infinite_mean"
        ,&territory_infinite_mean
        ,py::arg("x0 : initial position")
        ,py::arg("walker : our walker")
        ,py::arg("nbsteps : nb steps taken")
        ,py::arg("nbsimus")
        ,"returns the mean of explored territories after nbsteps averaged over nbsimus .");

handle.def("cover_time_mean"
        ,&cover_time_mean
        ,py::arg("walker : our walker")
        ,py::arg("size : size of ring (should be a double)")
        ,py::arg("nbsimus")
        ,"returns the mean cover time of the ring of size size,averaged over nbsimus .");

handle.def("cover_time_crossing_mean"
        ,&cover_time_crossing_mean
        ,py::arg("walker : our walker")
        ,py::arg("size : size of ring (should be a double)")
        ,py::arg("nbsimus")
        ,"returns the mean cover time of the ring of size size,averaged over nbsimus, in the crossing convention .");

handle.def("bounded_overshoot_distribution"
        ,&bounded_overshoot_distribution
        ,py::arg("x0")
        ,py::arg("size")
        ,py::arg("walker : our walker")
        ,py::arg("nbsimus")
        ,"returns the distribution of overshoots when escaping the interval.");
