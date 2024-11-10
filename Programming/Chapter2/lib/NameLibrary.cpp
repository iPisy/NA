#include"NameLibrary.hpp"
#include<algorithm>
#include<random>
#include<ctime>

using namespace std;

mt19937 generator(static_cast<unsigned int>(std::time(nullptr)));

NameLibrary::NameLibrary(const vector<string>& nameList):nameVector(nameList){
    shuffle(nameVector.begin(),nameVector.end(),generator);
}

string NameLibrary::getRandomName(){
    if(pos<nameVector.size()){
        return nameVector[pos++];
    }
    else return "UsedUp";
}