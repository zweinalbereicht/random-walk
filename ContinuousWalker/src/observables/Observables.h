#pragma once

#include <pybind11/pybind11.h>
#include <pybind11/iostream.h>
#include <pybind11/numpy.h>
#include <pybind11/stl.h>
#include <iostream>
#include <vector>
#include <string>
#include <stdlib.h>

#include "../walkers/ContinuousWalker.h"
#include "../walkers/GammaWalker.h"
#include "../walkers/LaplaceWalker.h"
#include "../walkers/LevyWalker.h"

namespace py = pybind11;

//renvoie la probability d'etre toujours en vie après n pas
double
survival_probability(const double x0,const long n, ContinuousWalker &walker, const long N);

//renvoie la probability de traverser x avant 0, partant de x0. On attend avant d'avoir N valeurs... -> ça peut prendre du temps
double
splitting_probability(const double x0,const double x, ContinuousWalker &walker, const long N);

//renvoie la distribution du temps de passage conditinnel à travers target(0=0,1=x), entre x et 0 
py::list
conditional_fpt_distribution(const double x0,const double x, ContinuousWalker &walker, const long N,const bool target=0);

//renvoie la moyenne du temps de passage conditionnel à travers target(0=0,1=x), entre x et 0 
double
conditional_fpt_mean(const double x0,const double x, ContinuousWalker &walker, const long N,const bool target=0);

