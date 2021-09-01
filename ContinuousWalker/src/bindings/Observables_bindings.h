#pragma once

handle.def("splitting_probability"
        ,&splitting_probability
        ,py::arg("x0")
        ,py::arg("x")
        ,py::arg("walker")
        ,py::arg("N")
        ,"returns the splitting probability to reach x before zero (crossing convention), averaged over N trials");

handle.def("survival_probability"
        ,&survival_probability
        ,py::arg("x0")
        ,py::arg("n")
        ,py::arg("walker")
        ,py::arg("N")
        ,"returns the survival probability after n steps, (crossing convention), averaged over N trials");

