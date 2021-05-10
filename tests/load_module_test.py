### Just another python script
import sys
import os
#print(sys.path)
print(os.getcwd())
sys.path.append(os.getcwd())

from  DiscreteWalker.build.module_DiscreteWalker import *
from  ContinuousWalker.build.module_ContinuousWalker import *

print("=============================================\n")

print("Let's load a BiasedWalker\n")
walker=BiasedWalker()
walker.print_details()
print("\n")

print("Let's load a SATWWalker\n")
walker=SATWWalker()
walker.print_details()
print("\n")

print("Let's load a LevyWalker\n")
walker=LevyWalker();
walker.print_details()
print("\n")

print("Let's load a LaplaceWalker\n")
walker=LaplaceWalker();
walker.print_details()
print("\n")

print("Let's load a GammaWalker\n")
walker=GammaWalker();
walker.print_details()
print("\n")

print("all walkers loaded with success!\n")

print("=============================================\n")
