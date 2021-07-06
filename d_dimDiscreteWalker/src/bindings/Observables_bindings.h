#pragma once

handle.def("fpt_arrival_bounded_distribution"
        ,&fpt_arrival_bounded_distribution,
        py::arg("s0"),
        py::arg("dimensions"),
        py::arg("walker"),
        py::arg("n")
        , "returns an array of n death times, starting from s0, on a periodic lattice defined by dimensions");

handle.def("fpt_arrival_bounded_global_mean"
        ,&fpt_arrival_bounded_global_mean
        ,py::arg("dimensions")
        ,py::arg("walker")
        ,py::arg("n")
        ,"returns the global mean first passage time to 0 on a ring of size N, over n trials, with the starting position averaged over a periodic lattice defined by dimensions");

handle.def("fpt_arrival_bounded_mean"
        ,&fpt_arrival_bounded_mean
        ,py::arg("s0")
        ,py::arg("dimensions")
        ,py::arg("walker")
        ,py::arg("n")
        ,"returns the mean first passage time to zero starting from s0 on a periodic lattice defined by dimensions, averaged over N trials");

handle.def("territory_distribution"
        ,&territory_distribution
        ,py::arg("s0")
        ,py::arg("dimensions")
        ,py::arg("walker")
        ,py::arg("n")
        , "returns an array of n covered territories, starting from s0, on a periodic lattice defined by dimensions");

handle.def("territory_global_mean"
        ,&territory_global_mean
        ,py::arg("dimensions")
        ,py::arg("walker")
        ,py::arg("n")
        ,"returns the global mean territory on a periodic lattice defined by dimensions, over n trials, with the starting position averaged over periodic lattice defined by dimensions");

handle.def("territory_mean"
        ,&territory_mean
        ,py::arg("s0")
        ,py::arg("dimensions")
        ,py::arg("walker")
        ,py::arg("n")
        ,"returns the mean territory covered starting from s0 on a periodic lattice defined by dimensions, averaged over n trials");

