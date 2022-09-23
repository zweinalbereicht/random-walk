import d_dimDiscreteWalker as md


walker=md.DiscreteWalker()
walker.print_details()
walker.set_seed(58364)
print(walker.get_seed())
nb_simus=10000
t=md.territory_unbounded_fixed_time_distribution([1,0],walker,3000,nb_simus)

print(t)

