import numpy as np
import sys
import isotropicWalker as md


walker = md.GaussianWalker()
walker.set_seed(np.random.randint(int(1e6)))

walker.print_details()
R_int = 10
R_out = 1000
print(md.split_prob_concentric_disk(R_int,R_out,walker,int(1000)))
