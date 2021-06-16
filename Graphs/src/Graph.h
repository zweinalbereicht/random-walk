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


//tools
void
split_line(const std::string line, std::vector<int> &vec);

void
show_matrix(std::vector<int> mat,int matsize);
