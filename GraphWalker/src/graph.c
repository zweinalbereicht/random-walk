#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <values.h>

#include "graph.h"

// All structures are defined in the .h file

Graph graph_create(int n){

    Graph g;
    int i;

    g=malloc(sizeof(struct graph)+sizeof(struct successors*)*(n)); // allocate space for the graph, that we shall free upon destroying the graph

    assert(g); // this is like a try/catch without the catch
    g->n=n;
    g->m=0;

    for(i=0;i<n;i++){
        g->alist[i]=malloc(sizeof(struct successors));
        assert(g->alist[i]);
        g->alist[i]->d=0;
        g->alist[i]->len=1;
        g->alist[i]->is_sorted=1;
    }

    return g;
}

void graph_destroy(Graph g){

    int i;
    for(i=0;i<g->n;i++){
        free(g->alist[i]);
    }
    free(g);

}

void graph_add_edge(Graph g, int u, int v){

    assert(u>=0);
    assert(u<g->n);
    assert(v>=0);
    assert(v<g->n);

    // prepare space
    while(g->alist[u]->d>=g->alist[u]->len){
        g->alist[u]->len*=2; // on double la taille pour que ce soit rapide
        g->alist[u]=realloc(g->alist[u],sizeof(struct successors)+sizeof(int)*(g->alist[u]->len-1));
    }

    //add new neighbor
    g->alist[u]->list[g->alist[u]->d++]=v; //d garde en mémoire le nombre de voisins, c'est par rapport à lui qu'on choisira un voisin au hasard.

    g->alist[u]->is_sorted=0;

    // update edge count
    g->m++;
}

void graph_add_undirected_edge(Graph g,int u,int v){

    graph_add_edge(g,u,v);
    graph_add_edge(g,v,u);

}

int graph_edge_count(Graph g){

    return g->m;

}

void graph_info(Graph g){

    int i;
    int j;
    printf("number of nodes : %d\n",g->n);
    for(i=0;i<g->n;i++){
        //printf("neighbors of %d: ",i);
        for(j=0;j<g->alist[i]->d;j++){
            printf("%d, ",g->alist[i]->list[j]);
        }
        printf("\n");
    }

}

// creates adjacency matrix from graph O(N²)
void make_matrix(Graph g,int* adja){


    int i;
    int j;

    for(i=0;i<g->n;i++){
        for(j=0;j<g->n;j++){
            adja[i+g->n*j]=0;
        }
    }

    for(i=0;i<g->n;i++){
        for(j=0;j<g->alist[i]->d;j++){
            adja[i+g->alist[i]->list[j]*g->n]=1;
        }
    }
}

// creates graph of n vertices with bonds specified in filenmae
Graph load_graph(int n, char * filename){

    Graph g=graph_create(n);

    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;
    char *ptr=NULL;
    int i;
    int j=0;

    fp = fopen(filename, "r");
    if (fp == NULL){
        printf("failed on first\n");
        exit(EXIT_FAILURE);
    }

    while ((read = getline(&line, &len, fp)) != -1) {
//        printf("Retrieved line of length %zu:\n", read);
//        printf("%s", line);

        char delim[] = " ";
        ptr = strtok(line, delim);

        while(ptr != NULL){
            i=atoi(ptr);
            graph_add_edge(g,j,i);
    //        printf("%d\n", i);
            ptr = strtok(NULL, delim);
        }
        j+=1;
     //   printf("%d\n", j);
    }

    fclose(fp);
    if (line)
        free(line);

    return g;
}

// Computes all shortes paths from one vertex to another
void floyd_warshall(int n, int *d){

    int i;
    int j;
    int k;
    int newdist;

    for(k=0;k<n;k++){
        for(i=0;i<n;i++){
            if(d[i+n*k]==MAXINT) continue;
            for(j=0;j<n;j++){
                if(d[k+n*j]==MAXINT) continue;

                newdist=d[i+n*k]+d[k+n*j];
                if(newdist<d[i+n*j]){
                    d[i+n*j]=newdist;
                }
            }
        }
    }
}

//displays matrix of size matsize*matsize
void display_matrix(int* mat, int matsize){

    for (int i=0;i<matsize;i++){
        for (int j=0;j<matsize;j++){
            printf("%d ",mat[i+matsize*j]);
        }
        printf("\n");
    }
    printf("\n");
}
