### Just another python script

import numpy as np
import sys
import time

import DiscreteWalker.build.module_DiscreteWalker as md

if __name__=='__main__':

    beta=0.01
    xmax=100
    nb_simus=1000000
    walker=md.SATWWalker(beta)
    walker.set_seed(int(time.time()+100000000))
    walker.print_details()

    print(md.rosenstock_fixed_time(2, walker, 4, 0.2, 100000))
    print((1/2*beta*(0.8)**2+(1/2)*(1-beta)*1/2*beta*(0.8)**3)/(1/2*beta+1/2**2*beta*(1-beta)))
