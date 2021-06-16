#!/bin/bash

#SBATCH --job-name=make_sp_Tgraph7
#SBATCH -t 7-00:00:00
#SBATCH -n 1
#SBATCH --mem-per-cpu=10000
#SBATCH --partition=normal
##SBATCH --output=%A.out
##SBATCH --error=%A.err
#SBATCH --mail-user=jeremie.klinger@polytechnique.org --mail-type=FAIL --mail-type=END
#SBATCH --exclude=saravone

hostname

nice -19 /users/invites/klinger/Projects/Territory/Tgraph/simulations/utils/make_sp


