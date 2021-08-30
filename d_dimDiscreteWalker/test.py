import numpy as np
import sys
import build.module_d_dimDiscreteWalker as md

walker = md.DiscreteWalker("just a simple walker", 2,
                           [1, 0], np.random.randint(100000))
walker.print_details()

a = int(sys.argv[1])
nb_sites = md.territory_unbounded_fixed_time_distribution(
    [1, 0], walker, 1, a)

print("mean nb of sites visited : \n")
print(nb_sites)
