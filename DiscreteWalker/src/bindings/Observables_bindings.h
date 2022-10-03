#pragma once

handle.def("fpt_arrival_bounded_distribution"
        ,&fpt_arrival_bounded_distribution,
        py::arg("s0"),
        py::arg("N"),
        py::arg("walker"),
        py::arg("n")
        , "returns an array of n death times, starting from s0, on a ring of size N");

handle.def("fpt_arrival_bounded_global_mean"
        ,&fpt_arrival_bounded_global_mean
        ,py::arg("N")
        ,py::arg("walker")
        ,py::arg("n")
        ,"returns the global mean first passage time to 0 on a ring of size N, over n trials, with the starting position averaged over the whole ring");

handle.def("fpt_arrival_bounded_mean"
        ,&fpt_arrival_bounded_mean
        ,py::arg("s0")
        ,py::arg("N")
        ,py::arg("walker")
        ,py::arg("n")
        ,"returns the mean first passage time to zero starting from s0 on a ring of size N, averaged over N trials");

handle.def("territory_distribution_fixed_time_infinite"
        ,&territory_distribution_fixed_time_infinite
        ,py::arg("s0")
        ,py::arg("walker")
        ,py::arg("nb_steps")
        ,py::arg("nb_simus")
        , "returns an array of nb_simus covered territories, starting from s0, after nb_steps taken in the infinite medium");

handle.def("territory_distribution"
        ,&territory_distribution
        ,py::arg("s0")
        ,py::arg("N")
        ,py::arg("walker")
        ,py::arg("n")
        , "returns an array of n covered territories, starting from s0, on a ring of size N");

handle.def("territory_distribution_infinite"
        ,&territory_distribution_infinite
        ,py::arg("s0")
        ,py::arg("max steps")
        ,py::arg("walker")
        ,py::arg("n")
        , "returns an array of n covered territories, starting from s0, in the infinite geometry. We limit the number of steps to n_steps");

handle.def("territory_global_mean"
        ,&territory_global_mean
        ,py::arg("N")
        ,py::arg("walker")
        ,py::arg("n")
        ,"returns the global mean territory on a ring of size N, over n trials, with the starting position averaged over the whole ring");

handle.def("territory_mean"
        ,&territory_mean
        ,py::arg("s0")
        ,py::arg("N")
        ,py::arg("walker")
        ,py::arg("n")
        ,"returns the mean territory covered starting from s0 on a ring of size N, averaged over n trials");

handle.def("map_of_explored_territory_distribution"
        ,&map_of_explored_territory_distribution
        ,py::arg("s0")
        ,py::arg("N")
        ,py::arg("walker")
        ,py::arg("nb_steps")
        ,py::arg("nb_simus")
        ,"returns an array of nb_simus maps, where a visited site is indicated by a 1, 0 otherwise. The walker performs nb_steps on this toroidal territory");

handle.def("territory_discovery_time_distribution"
        ,&territory_discovery_time_distribution
        ,py::arg("s0")
        ,py::arg("N")
        ,py::arg("walker")
        ,py::arg("nb_steps")
        ,py::arg("nb_simus")
        ,"returns an array of nb_simus timelines, where a timeline contains the times at which new sites were discovered. We limit the number of steps to nb_steps and evolve on a toroidal domain.");

handle.def("territory_infinite_discovery_time_distribution"
        ,&territory_infinite_discovery_time_distribution
        ,py::arg("s0")
        ,py::arg("walker")
        ,py::arg("nb_steps")
        ,py::arg("nb_simus")
        ,"returns an array of nb_simus timelines, where a timeline contains the times at which new sites were discovered. We limit the number of steps to nb_steps and evolve in an infinite domain.");

handle.def("rosenstock_fixed_time"
        ,&rosenstock_fixed_time
        ,py::arg("s0")
        ,py::arg("walker")
        ,py::arg("time")
        ,py::arg("rho")
        ,py::arg("n")
        ,py::arg("verbose")=0
        ,"returns the probability of a walker to have reacted with geometrically distributed targets of parameter rho kowning that it returned at the origin at time=time exactly. This estimation is averaged over n trials. We first record the maximum and then compute the probability of reaction");

handle.def("conditional_fpt_distribution"
        ,&conditional_fpt_distribution        
        ,py::arg("s0")
        ,py::arg("x")
        ,py::arg("walker")
        ,py::arg("N")
        ,py::arg("target")=1
        ,"returns N condtional fpt to 0 exactly if target = 0, or to x exactly if target = 1. the walker starts from s0. The program exists if the walker staets already on 0 or x or outside the interval");

handle.def("conditional_fpt_mean"
        ,&conditional_fpt_mean        
        ,py::arg("s0")
        ,py::arg("x")
        ,py::arg("walker")
        ,py::arg("N")
        ,py::arg("target")=1
        ,"returns an averaged (over N trails) fpt to 0 exactly if target = 0, or to x exactly if target = 1. the walker starts from s0. The program exists if the walker staets already on 0 or x or outside the interval");


handle.def("fpt_arrival_distribution"
        ,&fpt_arrival_distribution
        ,py::arg("s0")
        ,py::arg("max steps")
        ,py::arg("walker")
        ,py::arg("N")
        ,"returns an array of n arrival fpt, starting from s0, in the infinite geometry. We limit the number of steps to n_steps, so it will be a conditional distribution");

handle.def("survival_probability"
        ,&survival_probability
        ,py::arg("s0")
        ,py::arg("n")
        ,py::arg("walker")
        ,py::arg("N")
        ,"returns the survival probability after n steps, (the walker dies if he touches 0 excatly), averaged over N trials");


handle.def("splitting_probability"
        ,&splitting_probability
        ,py::arg("s0")
        ,py::arg("x")
        ,py::arg("walker")
        ,py::arg("N")
        ,"returns the splitting probability to reach x before zero (the walker stops when he touches exactly either boundary), averaged over N trials");
