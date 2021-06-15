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

handle.def("territory_distribution"
        ,&territory_distribution
        ,py::arg("s0")
        ,py::arg("N")
        ,py::arg("walker")
        ,py::arg("n")
        , "returns an array of n covered territories, starting from s0, on a ring of size N");

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

