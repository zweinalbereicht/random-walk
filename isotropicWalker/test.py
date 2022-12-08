import numpy as np
import sys
import isotropicWalker as md


walker = md.GaussianWalker()
walker.set_seed(np.random.randint(int(1e6)))

# walker.print_details()
R_int =20
offset  = 90
R_out = 23
theta0=np.pi
print(md.mfpt_2d_disk_outer_reflecting(R_int,R_out,walker,int(10000)))
# print(md.split_prob_concentric_disk(R_int,R_out,walker,int(10000)))
