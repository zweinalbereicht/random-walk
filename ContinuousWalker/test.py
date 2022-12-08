# Just another python script
import ContinuousWalker as md
import numpy as np

walker=md.LaplaceWalker()
walker.set_seed(np.random.randint(10000))
print(md.mfpt_bounded(0,1000,walker,100000))
