#include "Graph.h"


Graph::Graph(): m_n(1),m_m(0)
{}

Graph::Graph(const int n): m_n(n),m_m(0)
{
   int i;
   m_alist.resize(n);
   for(i=0;i<n;i++)
   {
        m_alist[i].m_d=0;
        m_alist[i].m_len=1;
        m_alist[i].m_isSorted=1;
   }
}


