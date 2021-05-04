### Just another python script
import sys
import os
#print(sys.path)
print(os.getcwd())
sys.path.append(os.getcwd())

from  DiscreteWalker.build.module_DiscreteWalker import *
from  SATWWalker.build.module_SATWWalker import *
from  RiemannWalker.build.module_RiemannWalker  import *

print("Let's load a RiemannWalker\n")
walker1=RiemannWalker()
walker1.print_details()
print("\n")
print("Let's load a SATWWalker\n")
walker2=SATWWalker()
walker2.print_details()
print("\n")
print("Let's load a DiscreteWalker\n")
walker3=pyDiscreteWalker()
walker3.print_details()
print("\n")

print("all walkers loaded with success!")
