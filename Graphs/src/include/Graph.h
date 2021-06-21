#pragma once

#include <vector>
#include <string>

struct relax_data
{
    int m_improved;
    int* m_dist;
    int* m_parent;
};

class Successors
{
    public:
    int m_d; //nb of actual successors
    int m_len; //nb of slots available
    char m_isSorted; // indicates if successor array is sorted or not
    std::vector<int> m_list; //list of successors initiated at 1

    Successors();
    ~Successors();
};

class Graph
{

    protected:
        int m_n; //nb of vertices
        int m_m; //nb of edges
        std::vector<int> m_adjacency; //adjecency matrix

    public:
        std::vector<Successors> m_alist; //neighbor list

    public:

        //constructeurs
        Graph(); //creates empty graph
        Graph(const int n); //creates graph with no edges
        Graph(const std::string filename); //creates graph from filename

        //desturucteurs
        ~Graph();

        //getters
        int get_n() const;

        //writers
        void write_adjacency(const std::string filename) const;

        //info functions
        void graph_info() const;
        void show_matrix() const;

        //build graph functions
        void add_edge(const int u, const int v);
        void add_undirected_edge(const int u,const int v);

        //useful functs on graphs
        std::vector<int>
        floyd_warshall() const;

};


/*------------------------------------------------------*/

//tools
void
split_line(const std::string line, std::vector<int> &vec);

void
show_matrix(std::vector<int> mat,int matsize);


//write a single matrix to a file
template <typename T>
void
write_matrix(const std::vector<T> &matrix, const int matsize, const std::string filename);

//load a songle matrix
std::vector<int>
load_matrix(const std::string filename, const int matsize);

//write pairs and the associatred chemical distance in a sorted way.
//valid only for non oriented graphs
void
write_chemical_distances(const std::vector<int> &matrix, const int matsize, std::string filename);

/*------------------------------------------------------*/

//generate all graph files from neighbor file

/*
we suppose the filename.txt file exists
filename.txt is a neighbor file, of the form

1 2
0 2
0 1

where the above is a triangular graph (0 is linked to 1 and 2 ...)
*/

void
create_all_graph_files_from_neighbors(const std::string filename);
