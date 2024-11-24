/**
 * @file
 * @brief Implement functions of class @ref LatexOutputer.
 */

#include"LatexOutputer.hpp"
#include"Exceptions.hpp"

LatexOutputer::LatexOutputer(const string& filename,bool moreColor):
file(filename),
colorLibrary(moreColor?
vector<string>{"black", "red", "green", "blue", "cyan", "magenta", "yellow", "orange", "purple", "brown", "lime", "olive", "pink", "teal", "violet", "gray", "darkgray", "lightgray"}
:
vector<string>{"black", "red", "green", "blue", "cyan", "magenta", "yellow", "orange"}
)
{
    file << "\\documentclass{standalone}\n"
    << "\\usepackage{pgfplots}\n"
    << "\\pgfplotsset{compat=1.16}\n"
    << "\\begin{document}\n";
}

void LatexOutputer::newImage(const string& imageName,const DefinitionDomain& definitionDomain){
    file << "\\begin{tikzpicture}\n"
    << "\\begin{axis}[\n"
    << "axis lines=middle,\n"
    << "xlabel=$x$, ylabel=$y$,\n"
    << "samples=200,\n";

    if(!definitionDomain.isDefault()){
        file << "domain="<<definitionDomain.get_l()<<":"<<definitionDomain.get_r()<<",\n";
    }
    
    file<< "title={"
    << imageName
    <<"},\n"
    << "enlargelimits,\n"
    <<"legend pos=outer north east"
    <<"]\n";
}


void LatexOutputer::addLine(const string& line,const DefinitionDomain& definitionDomain,const string& legendentry,const string& character){
    bool newLine=0;
    if(legendentry!="") newLine=1;
    if(newLine){
        color=colorLibrary.getRandomName();
        if(color=="UsedUp") throw ColorUsedUpException{};
    }
    linePreamble(character,definitionDomain,newLine);
    file<<line<<";\n";
    if(newLine){
        file<<"\\addlegendentry{"<<legendentry<<"}\n";
    }
}
void LatexOutputer::addLine(const string& line,const string& legendentry,const string& character,const DefinitionDomain& definitionDomain){
    addLine(line,definitionDomain,legendentry,character);
}

void LatexOutputer::linePreamble(const string& character,const DefinitionDomain& definitionDomain,bool newLine){
    file<<"\\addplot["<<color;
    if(character!="") file<<","<<character;
    if(!definitionDomain.isDefault()) file<<",domain="<<definitionDomain.get_l()<<":"<<definitionDomain.get_r();
    if(!newLine) file<<",forget plot";
    file<<"]";
}

void LatexOutputer::endImage(){
    file << "\\end{axis}\n"
    << "\\end{tikzpicture}\n";
    colorLibrary.reSet();
}

void LatexOutputer::endFile(){
    file << "\\end{document}\n";
    file.close();
}

void LatexOutputer::quickStart(const string& imageName,const DefinitionDomain& definitionDomain){
    newImage(imageName,definitionDomain);
}

void LatexOutputer::quickEnd(){
    endImage();
    endFile();
}