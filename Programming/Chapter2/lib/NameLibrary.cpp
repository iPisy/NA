/**
 * @file
 * @brief Implement functions of class @ref NameLibrary.
*/
#include"NameLibrary.hpp"
#include<algorithm>
#include<random>
#include<ctime>

using namespace std;

NameLibrary::NameLibrary(const vector<string>& nameList):nameVector(nameList){
    mt19937 generator(static_cast<unsigned int>(std::time(nullptr)));
    if(nameList.size()>=2) shuffle(nameVector.begin()+1,nameVector.end(),generator);
}

string NameLibrary::getRandomName(){
    if(pos<nameVector.size()){
        return nameVector[pos++];
    }
    else return "UsedUp";
}