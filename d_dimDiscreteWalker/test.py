import numpy as np
import build.module_d_dimDiscreteWalker as md

walker=md.DiscreteWalker("lala",3,[0,0,0],np.random.randint(100000))

walker.print_details()
for k in range(10):
    walker.move(1)

walker.print_details()
