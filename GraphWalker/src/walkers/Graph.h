#pragma once

#include <vector>
#include <string>

struct relax_data
{
    int m_improved;
    int* m_dist;
    int* m_parent;
};

struct successors
{
    int m_d; //nb of actual successors
    int m_len; //nb of slots available
    char m_isSorted; // indicates if successor array is sorted or not
    std::vector<int> m_list; //list of successors initiated at 1
};

class Graph
{

    protected:
        int m_n; //nb of vertices
        int m_m; //nb of edges
        std::vector<successors> m_alist;

    public:

        //constructeurs
        Graph(); //creates empty graph
        Graph(const int n); //created graph with no edges
        Graph(const char* filename); //creates graph from filename

        //desturucteurs
        ~Graph();

        void display_matrix() const;
};


