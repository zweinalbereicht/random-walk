import numpy as np
import d_dimDiscreteWalker as md

walker=md.DiscreteWalker()
walker.print_details()
walker.set_seed(np.random.randint(1000))

params={
    's0':[0,0],
    'n':30,
    'dimensions':[100,100],
    'walker':walker,
}
a=np.array(md.discovery_times_before_cover_distribution(**params))
print(np.mean(np.max(a,axis=1)),1/np.pi*1e4*np.log(1e4)**2)
