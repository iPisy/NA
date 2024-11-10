/**
 * @file
 * @brief implement functions in @ref LatexOutputer.
 */

#include"LatexOutputer.hpp"
#include"Exceptions.hpp"

LatexOutputer::LatexOutputer(string filename,bool moreColor):
file(filename),
color("black"),
colorLibrary(moreColor?
vector<string>{"red", "green", "blue", "cyan", "magenta", "yellow", "orange", "purple", "brown", "lime", "olive", "pink", "teal", "violet", "gray", "darkgray", "lightgray"}
:
vector<string>{"red", "green", "blue", "cyan", "magenta", "yellow", "orange"}
)
{
    file << "\\documentclass{standalone}\n"
    << "\\usepackage{pgfplots}\n"
    << "\\pgfplotsset{compat=1.16}\n"
    << "\\begin{document}\n";
}

void LatexOutputer::newImage(string imageName,double l,double r){
    file << "\\begin{tikzpicture}\n"
    << "\\begin{axis}[\n"
    << "axis lines=middle,\n"
    << "xlabel=$x$, ylabel=$y$,\n"
    << "samples=200,\n";

    if(l!=numeric_limits<double>::lowest() && r!=numeric_limits<double>::max()){
        file << "domain="<<l<<":"<<r<<",\n";
    }
    
    file<< "title={"
    << imageName
    <<"},\n"
    << "enlargelimits,\n"
    <<"legend pos=outer north east"
    <<"]\n";
}


void LatexOutputer::addLine(string line,double l,double r,string legendentry,string character){
    static bool firstCall=1;
    bool newLine=0;
    if(legendentry!="") newLine=1;
    if(firstCall && !newLine) throw InvalidInputException{};
    if(newLine && !firstCall){
        color=colorLibrary.getRandomName();
        if(color=="UsedUp") throw ColorUsedUpException{};
    }
    firstCall=0;
    linePreamble(character,l,r);
    file<<line<<";\n";
    if(newLine){
        file<<"\\addlegendentry{"<<legendentry<<"}\n";
    }
}
void LatexOutputer::addLine(string line,string legendentry,string character,double l,double r){
    addLine(line,l,r,legendentry,character);
}

void LatexOutputer::linePreamble(string character,double l,double r){
    file<<"\\addplot["<<color;
    if(character!="") file<<","<<character;
    if(l!=numeric_limits<double>::lowest() && r!=numeric_limits<double>::max()) file<<",domain="<<l<<":"<<r;
    file<<"]";
}

void LatexOutputer::endImage(){
    file << "\\end{axis}\n"
    << "\\end{tikzpicture}\n";
}

void LatexOutputer::endFile(){
    file << "\\end{document}\n";
    file.close();
}

void LatexOutputer::quickStart(string imageName,double l,double r){
    newImage(imageName,l,r);
}

void LatexOutputer::quickEnd(){
    endImage();
    endFile();
}