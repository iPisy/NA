/**
 * @file
 * @brief Declaration of class @ref NameLibrary.
*/
#pragma once
#include<vector>
#include<string>

using namespace std;

/**
 * @brief Store names and offer it at random with no repitition.
 */
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