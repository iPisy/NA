/**
 * @file
 * @brief implement functions in @ref LatexOutputer.
 */

#include"LatexOutputer.hpp"
#include"Exceptions.hpp"

void LatexOutputer::newImage(string imageName){
    file << "\\begin{tikzpicture}\n"
    << "\\begin{axis}[\n"
    << "    axis lines=center,\n"
    << "    xlabel=$x$, ylabel=$y$,\n"
    << "    title={"
    << imageName
    <<"},\n"
    << "    enlargelimits]\n";
}
    
void LatexOutputer::addLine(string line,string character,string legendentry){
    static bool firstCall=1;
    bool newLine=0;
    if(legendentry!="") newLine=1;
    if(newLine || firstCall){
        color=colorLibrary.getRandomName();
        if(color=="UsedUp") throw ColorUsedUpException{};
        firstCall=0;
    }
    linePreamble(character);
    file<<line<<"\n";
    if(newLine){
        file<<"\\addlegendentry{"<<legendentry<<"}\n";
    }
}

void LatexOutputer::linePreamble(string character){
    file<<"\\addplot["<<color;
    if(character!="") file<<","<<character;
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

void LatexOutputer::quickStart(string imageName){
    newImage(imageName);
}

void LatexOutputer::quickEnd(){
    endImage();
    endFile();
}