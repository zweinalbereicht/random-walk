#/bin/bash

# compiles all modules
for a in ContinuousWalker #d_dimDiscreteWalker #DiscreteWalker   GraphWalker isotropicWalker
do
    echo $a
    cd $a
    pip install .
    cd ..
done

echo ===============
