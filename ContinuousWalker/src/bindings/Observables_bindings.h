#pragma once

handle.def("splitting_probability"
        ,&splitting_probability
        ,py::arg("x0")
        ,py::arg("x")
        ,py::arg("walker")
        ,py::arg("N")
        ,"returns the splitting probability to reach x before zero (crossing convention), averaged over N trials.");

handle.def("survival_probability"
        ,&survival_probability
        ,py::arg("x0")
        ,py::arg("n")
        ,py::arg("walker")
        ,py::arg("N")
        ,"returns the survival probability after n steps, (crossing convention), averaged over N trials.");

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
