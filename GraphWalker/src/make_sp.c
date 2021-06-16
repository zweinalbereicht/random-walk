#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>
#include <time.h>
#include <values.h>

#include "tools.h"
#include "graph.h"

int main(){

    /* Parameters*/

    int size_graph=2188;
    char* filename="Tgraph7.txt";

    /* Useful variables*/

    int i;
    int j;
    Graph g; //graph on which to walk
    int *adja; //adjacency matrix
    int *sp; //shortest path matrix


    /* create objects*/

    g=load_graph(size_graph,filename);
    adja=malloc(sizeof(int)*g->n*g->n);
    sp=malloc(sizeof(int)*g->n*g->n);
    make_matrix(g,adja);

    //display_matrix(adja,g->n);
    //copy contents of adja into sp
    for(i=0;i<g->n;i++){
        for(j=0;j<g->n;j++){
            if(i==j){
                sp[i+g->n*j]=0;
            }
            else if(adja[i+g->n*j]==0){
                sp[i+g->n*j]=MAXINT;
            }
            else{
                sp[i+g->n*j]=adja[i+g->n*j];
            }
        }
    }

    /*---------------------------------------------*/

    // Make the shortestpath matrix
    floyd_warshall(size_graph,sp);
    //display_matrix(sp,size_graph);


    // save the shortestpath matrix
    drop_array(sp,g->n,"shortest_path_Tgraph7.txt");

    /*---------------------------------------------*/

    /* free all allocations */

    free(adja);
    free(sp);
    graph_destroy(g);

    return 0;

}
