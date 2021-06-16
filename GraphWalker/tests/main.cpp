#include <iostream>
#include <vector>
#include <limits>

#define Log(x) std::cout << x << std::endl;
#include <assert.h>

#include "../../Graphs/src/Graph.h"

int main(int argc, char** argv){

    std::vector<int> vec;

    Log("starting");

    std::string filename(argv[1]);
    Graph g(filename);
    vec=g.floyd_warshall();
    g.show_matrix();
    show_matrix(vec, g.get_n());

}
