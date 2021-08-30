#pragma once

handle.def("fpt_arrival_distribution"
        ,&fpt_arrival_distribution
        ,py::arg("s0")
        ,py::arg("target")
        ,py::arg("walker")
        ,py::arg("n")
        , "returns an array of n death times, starting from s0, and dying on the target");

handle.def("fpt_arrival_mean"
        ,&fpt_arrival_mean
        ,py::arg("s0")
        ,py::arg("target")
        ,py::arg("walker")
        ,py::arg("n")
        ,"returns the mean first passage time to zero starting from s0 and averaged over N trials");

handle.def("fpt_arrival_global_mean"
        ,&fpt_arrival_global_mean
        ,py::arg("target")
        ,py::arg("walker")
        ,py::arg("n")
        ,"returns the global mean first passage time to 0  over n trials, with the starting position averaged over the whole graph");

handle.def("territory_distribution"
        ,&territory_distribution
        ,py::arg("s0")
        ,py::arg("target")
        ,py::arg("walker")
        ,py::arg("n")
        , "returns an array of n covered territories, starting from s0, on the graph");

handle.def("territory_mean"
        ,&territory_mean
        ,py::arg("s0")
        ,py::arg("target")
        ,py::arg("walker")
        ,py::arg("n")
        ,"returns the mean territory covered starting from s0 on a ring of size N, averaged over n trials");

handle.def("territory_global_mean"
        ,&territory_global_mean
        ,py::arg("target")
        ,py::arg("walker")
        ,py::arg("n")
        ,"returns the global mean territory on a ring of size N, over n trials, with the starting position averaged over the whole ring");

handle.def("territory_fixed_time_distribution"
        ,&territory_fixed_time_distribution
        ,py::arg("s0")
        ,py::arg("target")
        ,py::arg("walker")
        ,py::arg("max_time")
        ,py::arg("n")
        , "returns an array of n covered territories, starting from s0, on the graph with a max_time threshold, after which the walker dies and the function returns an empty array");

handle.def("territory_fixed_time_mean"
        ,&territory_fixed_time_mean
        ,py::arg("s0")
        ,py::arg("target")
        ,py::arg("walker")
        ,py::arg("max_time")
        ,py::arg("n")
        ,"returns the mean territory covered starting from s0 on the graph before hitting the target, averaged over n trials,with a max_time threshold, after which the function returns zero ");

handle.def("territory_fixed_time_global_mean"
        ,&territory_fixed_time_global_mean
        ,py::arg("target")
        ,py::arg("walker")
        ,py::arg("max_time")
        ,py::arg("n")
        ,"returns the global mean territory on the graph, over n trials, with a max_time threshold, after which the function returns zero ");

handle.def("max_dist_territory_distribution"
        ,&max_dist_territory_distribution
        ,py::arg("s0")
        ,py::arg("target")
        ,py::arg("walker")
        ,py::arg("n")
        ,py::arg("filemane")
        ,"returns the joint distribution of the max distance and territory visited before hitting the target, starting from s0, with n values. The filemane argument indicates a path to the shortest path matrix needed to compute the max_distance. We return a list of the form [[territories],[distances]].");

handle.def("position_distribution"
        ,&position_distribution
        ,py::arg("s0")
        ,py::arg("steps")
        ,py::arg("walker")
        ,py::arg("n")
        ,"returns n positions after exactly 'steps' steps starting from s0");
