#pragma once

handle.def("split_prob_hyperplane"
        ,&split_prob_hyperplane
        ,py::arg("x0")
        ,py::arg("x")
        ,py::arg("walker")
        ,py::arg("n")
        , "return the splitting probability to cross the hyperplane defined by x before 0, starting from x0, evaluated using n trials");

handle.def("radial_distance_when_crossing_hyperplan_distribution"
        ,&radial_distance_when_crossing_hyperplan_distribution
        ,py::arg("x0")
        ,py::arg("x")
        ,py::arg("walker")
        ,py::arg("n")
        , "returns a distribution of n radial distances from the projection of the starting point corresponding the position of the walker after it crosses one of the hyperplanes for the first time.");

