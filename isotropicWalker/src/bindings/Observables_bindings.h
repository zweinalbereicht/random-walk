#pragma once

handle.def("split_prob_hyperplane"
        ,&split_prob_hyperplane
        ,py::arg("x0")
        ,py::arg("x")
        ,py::arg("walker")
        ,py::arg("n")
        , "return the splitting probability to cross the hyperplane defined by x before 0, starting from x0, evaluated using n trials");
