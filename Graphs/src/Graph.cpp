#include <iostream>
#include <fstream>
#include <string>
#include <limits>
#include "Graph.h"
#include <assert.h>
//#include <bits/stdc++.h>

/*------------------------------------------------------*/
//Successor constructors
Successors::Successors() : m_d(0),m_len(1),m_isSorted(1)
{}

Successors::~Successors()
{}

/*------------------------------------------------------*/
//Graph constructors
Graph::Graph(): m_n(1),m_m(0)
{
    m_alist.push_back(Successors());
    m_adjacency.push_back(0);
}


Graph::Graph(const int n): m_n(n),m_m(0)
{
   int i,j;
   for(i=0;i<m_n;i++)
   {
       m_alist.push_back(Successors());
       for(j=0;i<m_n;i++)
       {
           m_adjacency.push_back(0);
       }
   }
}

Graph::Graph(const std::string filename)
{
    m_n=0;
    std::string line;
    std::vector<int> vec;
    std::ifstream graph_file(filename);

    //find number of nodes
    if(graph_file.is_open())
    {
        //std::cout << "neatly opened" << std::endl;
        while(getline(graph_file,line))
            m_n++;
        graph_file.close();
    }
    else
        std::cout << "no such file as " << filename << std::endl;

    //prepare successor list and adjacency matrix
    int i,j;
    for(i=0;i<m_n;i++)
    {
        m_alist.push_back(Successors());
        for(j=0;j<m_n;j++)
        {
            m_adjacency.push_back(0);
        }
    }

    //reopen file
    i=0;
    graph_file.open(filename);
    if(graph_file.is_open())
    {
        while(getline(graph_file,line))
        {
            split_line(line, vec);
            for(auto x : vec)
                add_edge(i,x);
            i++;
        }
        graph_file.close();
    }
    else
        std::cout << "no such file as " << filename << std::endl;
}

//Graph destructor
Graph::~Graph()
{}

/*------------------------------------------------------*/
//getters

int
Graph::get_n() const
{
    return m_n;
}

/*------------------------------------------------------*/
//Graph fucntions

//displays
void
Graph::graph_info() const
{
    int i,j;
    std::cout << "number of nodes : " << m_n << std::endl;
    for(i=0;i<m_n;i++){
        std::cout << "node "<< i << std::endl;
        for(j=0;j<m_alist[i].m_d;j++){
            std::cout << m_alist[i].m_list[j] << ",";
        }
        std::cout << std::endl;
    }
}

void
Graph::show_matrix() const
{
    int i,j;
    for (i=0;i<m_n;i++){
        for (j=0;j<m_n;j++){
            std::cout << m_adjacency[m_n*i+j] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

/*------------------------------------------------------*/
//modifiers
void
Graph::add_edge(const int u, const int v)
{

    //checks on argument validity
    assert(u>=0);
    assert(v>=0);
    assert(u<m_n);
    assert(v<m_n);

    m_alist[u].m_list.push_back(v);
    m_alist[u].m_d++;

    m_alist[u].m_isSorted=0;

    //update adacency matrix
    m_adjacency[m_n*u+v]=1;

    // update edge count
    m_m++;
}


void
Graph::add_undirected_edge(const int u,const int v){
    add_edge(u,v);
    add_edge(v,u);
}

/*------------------------------------------------------*/
//useful funcs on graphs


std::vector<int>
Graph::floyd_warshall() const
{
    //on commence par faire une copie de la matrice d'adjacence
    std::vector<int> FW;
    int i,j,k,newdist;

    for(auto x : m_adjacency)
    {
        if(x==0)
            FW.push_back(INT_MAX);
        else
            FW.push_back(x);
    }
    for(int i=0;i<m_n;i++)
        FW[m_n*i+i]=0;

    //on lance l'algo
    for(k=0;k<m_n;k++){
        for(i=0;i<m_n;i++){
            if(FW[i+m_n*k]==INT_MAX) continue;
            for(j=0;j<m_n;j++){
                if(FW[k+m_n*j]==INT_MAX) continue;

                newdist=FW[i+m_n*k]+FW[k+m_n*j];
                if(newdist<FW[i+m_n*j]){
                    FW[i+m_n*j]=newdist;
                }
            }
        }
    }
    return FW;
}



/*------------------------------------------------------*/

//helper functions

//assuming the line is non empty

void
split_line(const std::string line, std::vector<int> &vec)
{
    vec.clear();
    std::string word="";

    for(auto x : line)
    {
        if (x == ' ')
        {
            vec.push_back(std::stoi(word));
            word = "";
        }
        else
        {
            word = word + x;
        }
    }
    //attention a la derniere lecture
    vec.push_back(std::stoi(word));
}

void
show_matrix(std::vector<int> mat,int matsize)
{

    int i,j;
    for (i=0;i<matsize;i++){
        for (j=0;j<matsize;j++){
            std::cout << mat[matsize*i+j] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}
