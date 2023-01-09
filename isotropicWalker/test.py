import numpy as np
import sys
import isotropicWalker as md


# walker = md.LevyWalker(1,0.5)
walker = md.GaussianWalker()
walker.print_details()
walker.set_seed(np.random.randint(int(1e6)))

# walker.print_details()
R_int =20
offset  = 10
R_out = 100
# r0=100
# theta=2*np.pi/2
r0=-50
theta0=0
nbsimus=int(1e0)
R=1e3
a=md.fpt_distribution_eccentric_inner_disk_outer_reflecting_any_position(R_int,R_out,offset,r0,theta0,walker,int(nbsimus))
print(np.mean(a))
# print(md.split_prob_concentric_disk(R_int,R_out,walker,int(10000)))
