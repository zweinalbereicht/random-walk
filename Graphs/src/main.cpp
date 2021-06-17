#include <iostream>
#include <vector>
#include "Graph.h"
#define Log(x) std::cout << x << std::endl

int main(int argc, char** argv)
{
    Log("compiled successfully");
    create_all_graph_files_from_neighbors("../graph_files/"+(std::string) argv[1]);
}
