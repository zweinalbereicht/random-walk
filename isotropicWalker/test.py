import numpy as np
import sys
import isotropicWalker as md


# # walker = md.LevyWalker(1,0.5)
# walker = md.GaussianWalker()
# walker.print_details()
# walker.set_seed(np.random.randint(int(1e6)))
#
# # walker.print_details()
# R_int =20
# offset  = 10
# R_out = 100
# # r0=100
# # theta=2*np.pi/2
# r0=-50
# theta0=0
# nbsimus=int(1e4)
# R=1e3
# m1=md.mfpt_2d_disk_outer_reflecting(R_int,R_out,walker,int(nbsimus))
# m2=np.mean(md.fpt_distribution_eccentric_inner_disk_outer_reflecting(R_int,R_out,0,0,walker,int(nbsimus)))
# m3=md.kac_flux_eccentric_inner_disk_outer_reflecting(R_int,R_out,0,walker,100,int(nbsimus))
# print(m1,m2,m3)
# # print(md.split_prob_concentric_disk(R_int,R_out,walker,int(10000)))

walker=md.RTLWalker()
a=md.trajectory(-19,walker,10)
print(a)
