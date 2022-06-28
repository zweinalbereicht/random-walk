# Just another python script
import numpy as np
import module_ContinuousWalker as md

walker = md.LaplaceWalker(100.0)
walker.print_details()

a = md.conditional_fpt_distribution(1.0, 10.0, walker, 10, 1)
print(a)





