import GraphWalker as md
import numpy as np
import os

os.chdir("./tests")
walker = md.GraphWalker("../../Graphs/graph_files/graph5.txt")

walker.print_details()
walker.set_seed(np.random.randint(2000))
print("lala")

print(len(md.territory_fixed_time_distribution(0, 1, walker, 2, 10)))
