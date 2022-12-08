import numpy as np
import sys
import isotropicWalker as md


walker = md.GaussianWalker()
walker.set_seed(np.random.randint(int(1e6)))

# walker.print_details()
R_int =10
offset  = 90
R_out = 100
theta0=np.pi
print(md.split_prob_eccentric_disk(R_int,R_out,offset,theta0,walker,int(10000)))
# print(md.split_prob_concentric_disk(R_int,R_out,walker,int(10000)))
