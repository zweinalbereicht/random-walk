#include <pybind11/pybind11.h>
#include <pybind11/iostream.h>
#include <iostream>
#include <vector>
#include <string>
#include <stdlib.h>

#include "DiscreteWalker.h"
#include "BiasedWalker.h"
#include "SATWWalker.h"
#include "RiemannWalker.h"

#include "Observables.h"

using namespace std;
namespace py = pybind11;

void first_test(const DiscreteWalker& walker)
{
    walker.print_details();
}

