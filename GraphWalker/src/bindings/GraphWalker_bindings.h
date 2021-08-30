#pragma once


py::class_<GraphWalker>(handle, "GraphWalker")

.def(py::init<>(),"default constructor")

.def(py::init<string,int,int>()
        ,py::arg("filename")
        ,py::arg("position")=0
        ,py::arg("seed")=1)

    .def("print_details",&GraphWalker::print_details
            ,py::call_guard<py::scoped_ostream_redirect>()//redirects cout to stdout in jupyter notebook
            ,"a function that prints details on the walker")

    .def("get_pos",&GraphWalker::get_pos
            ,"a getter function for the  walker's position")

    .def("get_lifetime",&GraphWalker::get_lifetime
            ,"a getter function for the  walker's lifetime")

    .def("get_filename",&GraphWalker::get_filename
            ,"a getter function for the  walker's graph filename")

    .def("get_seed",&GraphWalker::get_seed
            ,"a getter function for the  walker's seed")

    .def("get_graph_size",&GraphWalker::get_graph_size
            ,"a getter function for the  walker's graph size")

    .def("set_pos",&GraphWalker::set_pos
            ,py::arg("pos")
            ,"a setter function for the  walker's positon")

    .def("set_random_pos",&GraphWalker::set_random_pos
            ,"a setter function for the  walker, positioning it at random on the graph")

    .def("set_lifetime",&GraphWalker::set_lifetime
            ,py::arg("lifetime")
            ,"a setter function for the  walker's lifetime")

    .def("set_seed",&GraphWalker::set_seed
            ,py::arg("seed")
            ,"a setter function for the  walker's seed")

    .def("move",&GraphWalker::move
            ,py::call_guard<py::scoped_ostream_redirect>()
            ,py::arg("verbose")=0
            ,"a function that makes the walker perform a single step on one of its neighbors")

    .def("move_nsteps",&GraphWalker::move_nsteps
            ,py::call_guard<py::scoped_ostream_redirect>()
            ,py::arg("n")
            ,py::arg("verbose")=0
            ,"a function that makes the walker perform n steps")

    .def("move_til_death",&GraphWalker::move_til_death
            ,py::call_guard<py::scoped_ostream_redirect>()
            ,py::arg("target")
            ,py::arg("verbose")=0
            ,"a function that makes the walker walk until it reaches the target")

    .def("move_til_death",&GraphWalker::move_til_death
            ,py::call_guard<py::scoped_ostream_redirect>()
            ,py::arg("target")
            ,py::arg("verbose")=0
            ,"a function that makes the walker walk on the graph until it reaches the target")

    .def("isAlive",&GraphWalker::isAlive
            ,py::arg("target")
            ,"a function that says if the walker is still alive")

    .def("move_fixed_time",&GraphWalker::move_fixed_time
            ,py::arg("target")
            ,py::arg("time")
            ,"a function that makes the walker for a fixed time period. The function returns 0 if the walker died exactly on its nth step, 1 else.")
    ;

