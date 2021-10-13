#pragma once


py::class_<GaussianWalker>(handle, "GaussianWalker")

    .def(py::init<>(),"default constructor")

    .def(py::init<string,int, pybind11::list &,int>()
        ,py::arg("name")
        ,py::arg("dimension")
        ,py::arg("position")
        ,py::arg("seed"))

    .def("print_details",&GaussianWalker::print_details
            ,py::call_guard<py::scoped_ostream_redirect>()//redirects cout to stdout in jupyter notebook
            ,"a function that prints details on the walker")

    .def("get_pos",&GaussianWalker::get_pos
            ,"a getter function for the  walker's position")

    .def("get_direction",&GaussianWalker::get_direction
            ,"a getter function for the  walker's direction")

    .def("get_max",&GaussianWalker::get_max
            ,"a getter function for the  walker's maximum")

    .def("get_lifetime",&GaussianWalker::get_lifetime
            ,"a getter function for the  walker's lifetime")

    .def("get_seed",&GaussianWalker::get_seed
            ,"a getter function for the  walker's seed")

    .def("set_pos",&GaussianWalker::set_pos
            ,py::arg("pos")
            ,"a setter function for the  walker's positonn")

    .def("set_direction",&GaussianWalker::set_direction
            ,py::arg("pos")
            ,"a setter function for the  walker's direction")

    .def("set_max",&GaussianWalker::set_max
            ,py::arg("max")
            ,"a setter function for the  walker's maximum")

    .def("set_lifetime",&GaussianWalker::set_lifetime
            ,py::arg("lifetime")
            ,"a setter function for the  walker's lifetime")

    .def("set_seed",&GaussianWalker::set_seed
            ,py::arg("seed")
            ,"a setter function for the  walker's seed")

    .def("set_random_pos",&GaussianWalker::set_random_pos
            ,py::arg("dimensions")
            ,"sets the walker uniformely somewhere in the bow defined by dimensions")

    .def("move",&GaussianWalker::move
            ,py::call_guard<py::scoped_ostream_redirect>()
            ,py::arg("verbose")=0
            ,"a function that makes the walker perform a single step, the default choice being an isotrobic gaussian distributed step ")

    //need to do this if we want polymorphism activated
    .def("move_bounded",&GaussianWalker::move_bounded
            ,py::call_guard<py::scoped_ostream_redirect>()
            ,py::arg("dimensions")
            ,py::arg("verbose")=0
            ,"a function that makes the walker perform a single step on a periodic d-dimensionnal space, the default choice being an isotropic gaussian distributed step")

    .def("move_til_death",&GaussianWalker::move_til_death
            ,py::call_guard<py::scoped_ostream_redirect>()
            ,py::arg("verbose")=0
            ,"a function that makes the walker walk until it reaches zero exactly")

    .def("move_til_death_bounded",&GaussianWalker::move_til_death_bounded
            ,py::call_guard<py::scoped_ostream_redirect>()
            ,py::arg("dimensions")
            ,py::arg("verbose")=0
            ,"a function that makes the walker walk until it reaches zero on a periodic lattices with sizes defined in the dimensions list")

/*
    .def("move_til_death_bounded_record_territory",&GaussianWalker::move_til_death_bounded_record_territory
            ,py::call_guard<py::scoped_ostream_redirect>()
            ,py::arg("dimensions")
            ,py::arg("verbose")=0
            ,"a function that makes the walker walk until it reaches zero on a periodic lattices with sizes defined in the dimensions list, and returns the number of sites visited")
*/
    .def("isAlive",&GaussianWalker::isAlive
            ,"a function that says if the walker is still alive")

    .def("move_fixed_time",&GaussianWalker::move_fixed_time
            ,py::arg("time")
            ,"a function that makes the walker perform exactly time steps")

;

