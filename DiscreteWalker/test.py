### Just another python script
import numpy as np
import DiscreteWalker as md

walker=md.RiemannWalker(2.0,0.5)
walker.set_seed(np.random.randint(100000))
walker.print_details()

#print("\n")
#
#s0,N,n=5,10,1000000
#print("starting pos : {0} size of ring : {1} number of trials {2}".format(s0,N,n))
#a=np.array(md.first_test(s0,N,walker,n))
#
#print("\n")
#print("first passage times \n")
##print(a)
#print(len(a))
#print(a)
