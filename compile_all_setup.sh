#/bin/bash

# compiles all modules
for a in ContinuousWalker DiscreteWalker d_dimDiscreteWalker GraphWalker isotropicWalker
do
    echo $a
    cd $a
    pip install .
    cd ..
done

echo ===============
