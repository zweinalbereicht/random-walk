#pragma once

handle.def("split_prob_hyperplane"
        ,&split_prob_hyperplane
        ,py::arg("x0")
        ,py::arg("x")
        ,py::arg("walker")
        ,py::arg("n")
        , "return the splitting probability to cross the hyperplane defined by x before 0, starting from x0, evaluated using n trials");


handle.def("split_prob_cone"
        ,&split_prob_cone
        ,py::arg("r0")
        ,py::arg("theta0")
        ,py::arg("theta")
        ,py::arg("walker")
        ,py::arg("n")
        , "return the probability to escape through the upper side of the cone, defined by its angle theta");

handle.def("split_prob_reflecting_cone"
        ,&split_prob_reflecting_cone
        ,py::arg("r0")
        ,py::arg("theta0")
        ,py::arg("theta")
        ,py::arg("R")
        ,py::arg("walker")
        ,py::arg("n")
        , "return the probability to escape through the upper side of the cone, defined by its angle theta, with a reflecting BC on the arc at r=R");

handle.def("radial_distance_when_crossing_hyperplan_distribution"
        ,&radial_distance_when_crossing_hyperplan_distribution
        ,py::arg("x0")
        ,py::arg("x")
        ,py::arg("walker")
        ,py::arg("n")
        , "returns a distribution of n radial distances from the projection of the starting point corresponding the position of the walker after it crosses one of the hyperplanes for the first time.");


handle.def("split_prob_disk_escape"
        ,&split_prob_disk_escape
        ,py::arg("R")
        ,py::arg("theta1")
        ,py::arg("theta2")
        ,py::arg("walker")
        ,py::arg("n")
        , "returns the probability to escape the disk of radius R, centered at 0 and to be located in the arc [theta1, theta2]. For simplicity, the walker always starts at r=R and theta=PI");

handle.def("split_prob_concentric_disk"
        ,&split_prob_concentric_disk
        ,py::arg("inner_radius")
        ,py::arg("outer_radius")
        ,py::arg("walker")
        ,py::arg("n")
        , "returns the probability to escape concentric discs via the farthest one." );

handle.def("survival_disk"
        ,&survival_disk
        ,py::arg("R")
        ,py::arg("nbsteps")
        ,py::arg("walker")
        ,py::arg("n")
        , "returns the probability to survive nbsteps steps in a disk of radiius R");
