import numpy as np
import d_dimDiscreteWalker as md

walker=md.DiscreteWalker()
walker.print_details()
walker.set_seed(np.random.randint(1000))

a=np.array(md.discovery_times_before_cover_distribution([10,10],[0,0],walker,300))
print(np.mean(np.max(a,axis=1)),1/np.pi*100*np.log(100)**2)
