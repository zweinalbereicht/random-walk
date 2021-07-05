import numpy as np
import sys
import build.module_d_dimDiscreteWalker as md

walker=md.DiscreteWalker("lala",3,[0,0,0],np.random.randint(100000))

walker.print_details()
for k in range(int(sys.argv[1])):
    walker.move(0)

walker.print_details()
