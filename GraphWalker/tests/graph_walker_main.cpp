#include <iostream>
#include <vector>
#include <limits>

#define Log(x) std::cout << x << std::endl;
#include <assert.h>

#include "../../Graphs/src/Graph.h"
#include "../src/walkers/GraphWalker.h"
#include "../src/observables/Observables.h"

int main(int argc, char** argv){

    std::string filename(argv[1]);
    GraphWalker walker(filename);
    walker.set_random_pos();
    walker.print_details();
    int i;
    Log("\n");
    std::cout << walker.get_pos() << " -> ";
    for(i=0;i<std::stoi(argv[2]);i++)
        walker.move(1);
    Log("DONE\n");
    walker.print_details();
}
