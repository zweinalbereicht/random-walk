#include <iostream>
#include "../include/Graph.h"

int main(int argc, char** argv)
{
    if(argc!=3)
    {
        std::cout << "not enough/too many arguments, only expect 2 : filename and matsize" << std::endl;
        exit(0);
    }
    else
    {
        int matsize = std::stoi(argv[2]);
        std::string path;
        path = (std::string) argv[1];
        //on enleve l'extension.txt
        path.resize(path.size()-4);
        std::vector<int> FW;
        FW=load_matrix(path+"_SP.txt",matsize);
        if(FW.size()>0)
        {
            //std::cout << FW.size() << std::endl;
            //show_matrix(FW,matsize);
            write_chemical_distances(FW, matsize, path+"_chemdist.txt");
        }
        exit(0);
    }
}
