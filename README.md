# This project contains various Cpp based python modules I use in my PhD work. 

## description
Available modules are:
- DiscreteWalker (1d lattice random walks)
- ContinuousWalker (jump processses on the real line)
- d_dimDiscreteWalker (multi dimensionnal discrete random walks)
- isotropicWalker (isotropic jump processes in R^2)
- GraphWalker (nearest neighbor diffusion on arbitrary graphs)

use the 
```python
import DiscreteWalker as md
help(md)
```
in any python interpreter to see a description of possibilities with the modules.

## installation

Execute "bash compile_all_setup.sh" to compile all at once, or run 
```python
pip install .
```
in the desired module directory.

## disclaimer

I'm consta,tly updating, changing and trying things out, hence the chaotic structure of the repo...it might change some day 😬😬
