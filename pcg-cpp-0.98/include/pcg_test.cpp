#pragma once

#include <iostream>
#include <stdlib.h>
#include <random>
#include <gsl/gsl_rng.h>
#include "pcg_random.hpp"


typedef struct //mimicking the mt_state_t declaration
{
    pcg32* rng;
} gsl_pcg_state;

static void
gsl_pcg_set(void *state, unsigned long int s)
{
    pcg_extras::seed_seq_from<std::random_device> seed_source;
    static pcg32 rng_init(seed_source); //on initialise un generateur pcg de maniere completement non controlée pour ll'instant!!

    (((gsl_pcg_state *) state)->rng) = &rng_init; //on mappe l'aresse dans l'eta
    (void) s; // ne nous sert à rien puisqu'on controle pas le seeding
}

static unsigned long int
gsl_pcg_get(void *state)
{
    return (*(((gsl_pcg_state *) state)->rng))();
}

static double
gsl_pcg_get_double(void *state) //returns smth in the range (0,1)
{
    return gsl_pcg_get(state) / 4294967296.0 ;
}

static const gsl_rng_type gsl_rng_pcg_type =
{
    "gsl_rng_pcg",
    0xffffffffUL,
    0,
    sizeof(gsl_pcg_state),
    &gsl_pcg_set,
    &gsl_pcg_get,
    &gsl_pcg_get_double
};

static const gsl_rng_type *gsl_rng_pcg = &gsl_rng_pcg_type;
