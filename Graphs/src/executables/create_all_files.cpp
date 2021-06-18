#include <iostream>
#include <vector>
#include "../include/Graph.h"
#define Log(x) std::cout << x << std::endl

int main(int argc, char** argv)
{
    if(argc>2)
    {
        std::cout << "too many args, input exact path or none" << std::endl;
        std::exit(0);
    }
    else
    {

        std::string path;
        if(argc==1)
        {
            std::cout << "enter graph neighbor list, we will generate adacency, Floyd Warshall and pair list files" << std::endl;
            std::cin >> path;
        }
        else
            path = (std::string) argv[1];

        path.resize(path.size()-4);
        create_all_graph_files_from_neighbors(path);
        exit(0);

    }
}
