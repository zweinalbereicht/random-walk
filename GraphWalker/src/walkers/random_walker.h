#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>

#include "graph.h"

struct walker{
    int pos;
    int* grid;
};


typedef struct walker *Walker;

Walker make_walker(int start,Graph g);

void kill_walker(Walker w);

int walker_position(Walker w);

void move_walker(Walker w,Graph g,gsl_rng * rng);

void display_grid(Walker w,Graph g);

void walk_til_death(Walker w,Graph g, int start, int target,gsl_rng * rng);
