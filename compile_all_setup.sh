#/bin/bash

# compiles all modules
for a in d_dimDiscreteWalker #DiscreteWalker #ContinuousWalker GraphWalker isotropicWalker
do
    echo $a
    cd $a
    pip install .
    cd ..
done

echo ===============
