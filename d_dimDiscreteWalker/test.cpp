#include <iostream>
#include <map>
#include <string>
#include <vector>

//useful shorthands
#define LOG(x) std::cout << x << std::endl
#define MOD(x,b) (x % b + b) % b

int main(){
    std::vector<int> pos1{ 1,2,3};
    std::vector<int> pos2{ 2,4,6};
    std::map<std::vector<int>, int> territory;

    territory[pos1]=1;
    territory[pos2]=2;
    territory[pos1]=3;

    for(auto x : territory){
        LOG("key");
        for(int i=0;i<x.first.size();i++)
            LOG(x.first[i]);
        LOG("value");
        LOG(x.second);
    }

}
