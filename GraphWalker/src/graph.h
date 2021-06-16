#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>


// useful structure for chemical distance algorithms
struct relax_data{
    int improved;
    int *dist;
    int *parent;
};

struct graph {

    int n;
    int m;
    struct successors { // we define the structure in there but maybe we should try to define it outside for clarity...
        int d; //number of actual successors
        int len; //nb of slots available in the array
        char is_sorted; //indicates if successor array is sorted or not
        int list[1]; //list of successors that has already length 1
    } *alist[1]; //this is a list of the successor listss

};

//on définit un pointeur vers un graph comme Graph
typedef struct graph *Graph;

// create graph with no edges
Graph graph_create(int n);

//create graph from adjacency matrix
Graph graph_create_frommatrix(int* matrix);

// free associated space
void graph_destroy(Graph g);

// Add edge to graph from source to sink
void graph_add_edge(Graph, int source, int sink);

// Add the two edges as un undirected graph
void graph_add_undirected_edge(Graph g,int u,int v);

// general things about the graph
int graph_vertex_count(Graph g);
int graph_edge_count(Graph g);

// Prints a lsit of the links
void graph_info(Graph g);


//make adjacency matrix from graph
void make_matrix(Graph g,int* adja);

Graph load_graph(int n, char * filename);


// implementing the shortest path for all points method
void floyd_warshall(int n, int *d);

//displays matrix
void display_matrix(int* mat, int matsize);
