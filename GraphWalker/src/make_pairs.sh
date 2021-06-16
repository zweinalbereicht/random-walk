#!/bin/bash
#SBATCH --job-name=make_pairs_Tgraph_9
#SBATCH -t 7-00:00:00
#SBATCH -n 1
#SBATCH --mem-per-cpu=10000
#SBATCH --partition=normal
#SBATCH --output=%A.out
#SBATCH --error=%A.err
##SBATCH --mail-user=jeremie.klinger@polytechnique.org --mail-type=FAIL --mail-type=END
#SBATCH --exclude=saravone


hostname

sp=shortest_path_Tgraph9.txt
nb_pairs=500
dist_limit=6

for i in $(seq 6 7)
do

    f_output=pairs9_$i.txt


    nice -19 python /users/invites/klinger/Projects/Territory/Tgraph/simulations/utils/gen_close_pairs.py $sp $f_output $nb_pairs $dist_limit

done
