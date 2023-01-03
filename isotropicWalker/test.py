import numpy as np
import sys
import isotropicWalker as md


walker = md.LevyWalker(1,0.5)
# walker = md.GaussianWalker()
walker.print_details()
walker.set_seed(np.random.randint(int(1e6)))

# walker.print_details()
# R_int =20
# offset  = 90
# R_out = 23
r0=100
theta=2*np.pi/2
theta0=np.pi/4
nbsimus=100000
R=1e3
print(md.split_prob_reflecting_cone(r0,theta0,theta,R,walker,int(nbsimus)))
# print(md.split_prob_concentric_disk(R_int,R_out,walker,int(10000)))
