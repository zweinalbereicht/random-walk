# Just another python script
import ContinuousWalker as md
import numpy as np

walker=md.LevyWalker(1,1.2)
walker.set_seed(np.random.randint(10000))
walker.set_pos(0)
walker.set_lifetime(0)
a=md.cover_time_crossing_mean(walker, 10,10)
print(a)
