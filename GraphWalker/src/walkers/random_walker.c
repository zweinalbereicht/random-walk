#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>

#include "random_walker.h"

Walker make_walker(int start,Graph g){

    Walker w;
    w=malloc(sizeof(struct walker));
    w->pos=start;
    w->grid=malloc(sizeof(int)*g->n);

    for(int i=0;i<g->n;i++){
        w->grid[i]=0;
    }

    w->grid[w->pos]+=1;

    return w;

}

void kill_walker(Walker w){
    free(w->grid);
    free(w);
};

// return the walker's position
int walker_position(Walker w){
    return w->pos;
}

//move the walker
void move_walker(Walker w,Graph g,gsl_rng * rng){

    int nb_neighbors=g->alist[w->pos]->d;
    //printf("%d\n",nb_neighbors);
    //printf("%d\n",gsl_rng_uniform_int(rng,nb_neighbors)); // on a 4 possibilités de transition
    w->pos=g->alist[w->pos]->list[gsl_rng_uniform_int(rng,nb_neighbors)]; // on a 4 possibilités de transition
    w->grid[w->pos]+=1;

}

void display_grid(Walker w,Graph g){

    for(int i=0;i<g->n;i++){
        printf("%d ",w->grid[i]);
    }
    printf("\n");

}

// resets walke and walk untl target is found
void walk_til_death(Walker w,Graph g, int start, int target,gsl_rng * rng){

    w->pos=start;
    for(int i=0;i<g->n;i++){
        w->grid[i]=0;
    }
    w->grid[w->pos]+=1;
    while(w->pos!=target){
        move_walker(w,g,rng);
    }

}
