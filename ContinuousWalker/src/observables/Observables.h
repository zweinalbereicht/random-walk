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

double
//renvoie la probability d'etre toujours en vie après n pas
survival_probability(const double x0,const long n, ContinuousWalker &walker, const long N);

//renvoie la probability d'etre toujours en vie après n pas dans un intervalle
double
survival_probability_bounded(const double x0, const double x, const long n, ContinuousWalker &walker, const long N);

//renvoie la probability de traverser x avant 0, partant de x0. On attend avant d'avoir N valeurs... -> ça peut prendre du temps
double
splitting_probability(const double x0,const double x, ContinuousWalker &walker, const long N);

//renvoie la distribution du temps de passage conditinnel à travers target(0=0,1=x), entre x et 0 
py::list
conditional_fpt_distribution(const double x0,const double x, ContinuousWalker &walker, const long N,const bool target=0);

//renvoie la moyenne du temps de passage conditionnel à travers target(0=0,1=x), entre x et 0 
double
conditional_fpt_mean(const double x0,const double x, ContinuousWalker &walker, const long N,const bool target=0);

//renvoie la probabilité de sortir à travers 0 au temps n exactement
double
fpt_probability(const double x0, ContinuousWalker &walker, const long n,const long N);


//renvoie la probabilité de sortir coté target au temps n exactement
double
conditional_fpt_probability(const double x0,const double x, ContinuousWalker &walker, const long n,const long N,const bool target=0);

//renvoie la probabilité de sortir d'un intervalle au temps n exactement
double
unconditional_fpt_probability(const double x0,const double x, ContinuousWalker &walker, const long n,const long N);


//renvoie la distribution du max s'il est atteint au n-ième pas, qui est aussi le dernier . L'option bounded_below permet de mettre une bnarrière absorvante en 0.
py::list
max_on_last_step_distribution(const double x0, ContinuousWalker &walker, const long n,const long N,const bool bounded_below=0);

//renvoie la distribution du max avant de traverser 0 pour la premiere fois, s'il est atteint au n-ième pas.  
py::list
time_conditioned_max_before_exit_distribution(const double x0, ContinuousWalker &walker, const long n,const long N);

//renvoie la distribution du max s'il est atteint au n-ième pas.  
py::list
time_conditioned_max_distribution(const double x0, ContinuousWalker &walker, const long n,const long nMax,const long N);
