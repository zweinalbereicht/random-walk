### Just another python script

import numpy as np
import sys
import time

import DiscreteWalker.build.module_DiscreteWalker as md

if __name__=='__main__':

    beta=0.7
    xmax=100
    nb_simus=1000000
    walker=md.SATWWalker(beta)
    walker.set_seed(int(time.time()+100000000))
    walker.print_details()

    result=walker.max_prob(1,xmax,nb_simus)
    print("prob : {0:e}".format(result))
