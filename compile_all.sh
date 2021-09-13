#/bin/bash

#for a in $(ls | grep Walker)
echo $PATH
for a in d_dimDiscreteWalker GraphWalker Graphs DiscreteWalker ContinuousWalker
do
    echo $a
    cd $a
    rm -rf build
    mkdir build
    cd build
    cmake ../
    make
    export PATH="$(pwd):$PATH"
    cd ..
    cd ..
done

echo ===============

echo  TESTING THE LOAD

#python tests/load_module_test.py

echo ===============
echo $PATH
path=/home/invites/klinger/Libraries/random-walk/
path2=/users/invites/klinger/Projects/Libraries/random-walk/
cd $path2
rm -rf *
cp $(find $path -name module*.so) .
cd $path
echo "modules copied to" $path2

