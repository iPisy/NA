/**
 * @file 
 * @brief declaration of class @ref LatexOutputer.
 */

#pragma once
#include<fstream>
#include<string>
#include"NameLibrary.hpp"

using namespace std;

/**
 * @brief Enable outputing image of @ref Function, @ref Curve, etc. in .tex files, 
 * which can be compiled into .pdf files, presenting the image.
 * 
 * an object of @ref LatexOutputer correspond one-to-one with a file.
 */
class LatexOutputer{
public:

    /**
     * @brief ctor. It will add preamble to the generated file.
     */
    LatexOutputer(string filename):
    file(filename),
    colorLibrary(vector<string>{"black", "red", "green", "blue", "cyan", "magenta", "yellow",
    "orange", "purple", "brown", "lime", "olive", "pink", "teal", "violet", "gray", "darkgray", "lightgray"})
    {
        file << "\\documentclass{standalone}\n"
        << "\\usepackage{pgfplots}\n"
        << "\\pgfplotsset{compat=1.16}\n"
        << "\\begin{document}\n";
    }

    /**
     * @brief Add a new image to .tex file.
     */
    void newImage(string imageName);

    /**
     * @brief Add a line into the image of .tex file.
     * 
     * @param line the line to plot, in calculatable Latex format. If there are more than 1 line, use ',' to separate.
     * @param legendentry the legendentry to add, in format "$...$". If not offered, it will not add legendentry. 
     * A new legendentry implies a new line, thus the color of the line should change accordingly.
     * @param character the character of the line, choosing from "thick", "dashed", etc.
     */
    void addLine(string line,string character="",string legendentry="");

    /**
     * @brief call when the image is completed. Add appendix of Image.
     */
    void endImage();

    /**
     * @brief call when the file is completed. Add appendix of file, i.e. "\end{doucument}".
     */
    void endFile();

    /**
     * @brief Used when only need to plot single image. Before start.
     */
    void quickStart(string imageName);

    /**
     * @brief Used when only need to plot single image. After ploting.
     */
    void quickEnd();

private:
    /**
     * @brief Output preamble of a line.
     */
    void linePreamble(string character);

    ofstream file;///< the file to put in.

    string color;///< the color of the line at present.

    NameLibrary colorLibrary;///< offer many sort of colors.
};
