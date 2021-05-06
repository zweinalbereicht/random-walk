### Just another python script
import sys
import os
#print(sys.path)
print(os.getcwd())
sys.path.append(os.getcwd())

from  DiscreteWalker.build.module_DiscreteWalker import *
from  SATWWalker.build.module_SATWWalker import *
from  RiemannWalker.build.module_RiemannWalker  import *
from  ContinuousWalker.build.module_ContinuousWalker  import *

print("=============================================\n")

print("Let's load a RiemannWalker\n")
walker=RiemannWalker()
walker.print_details()
print("\n")

print("Let's load a SATWWalker\n")
walker=SATWWalker()
walker.print_details()
print("\n")

print("Let's load a DiscreteWalker\n")
walker=pyDiscreteWalker()
walker.print_details()
print("\n")

print("Let's load a ContinuousWalker\n")
walker=ContinuousWalker()
walker.print_details()
print("\n")

print("all walkers loaded with success!\n")

print("=============================================\n")
