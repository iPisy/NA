#pragma once
#include<vector>
#include<string>

using namespace std;

class NameLibrary{
public:
    NameLibrary(const vector<string>& nameList);
    string getRandomName();
    void reSet(){
        pos=0;
    }
private:
    vector<string> nameVector;
    int pos=0;
};