#/bin/bash

#for a in $(ls | grep Walker)
for a in GraphWalker Graphs #DiscreteWalker ContinuousWalker
do
    echo $a
    cd $a
    rm -rf build
    mkdir build
    cd build
    cmake ..
    make
    export PATH="$(pwd):$PATH"
    cd ..
    cd ..
done

echo ===============

echo  TESTING THE LOAD

#python tests/load_module_test.py

echo ===============
