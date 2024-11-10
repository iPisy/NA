/**
 * @file 
 * @brief Declaration of class @ref LatexOutputer.
 */

#pragma once
#include<fstream>
#include<string>
#include<limits>
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
     * 
     * @param moreColor ==0: max 8 colors. ==1: max 18 colors, but may be hard to recognize.
     */
    LatexOutputer(string filename,bool moreColor=0);

    /**
     * @brief Add a new image to .tex file.
     */
    void newImage(string imageName,double l=numeric_limits<double>::lowest(),double r=numeric_limits<double>::max());

    /**
     * @brief Add a line into the image of .tex file.
     * 
     * @param line the line to plot, in calculatable Latex format, like {sin(x)} or ({sin(x)},{cos(x)}).
     * @param l left endpoint of definition domain.
     * @param r right endpoint of definition domain.
     * @param legendentry the legendentry to add, in Latex math format "$...$" or just text. 
     * If not offered, it will not add legendentry. 
     * A new legendentry implies a new line, thus the color of the line should change accordingly.
     * @param character the character of the line, choosing from "thick", "dashed", etc.
     */
    void addLine(string line,double l=numeric_limits<double>::lowest(),double r=numeric_limits<double>::max(),string legendentry="",string character="");
    void addLine(string line,string legendentry,string character="",double l=numeric_limits<double>::lowest(),double r=numeric_limits<double>::max());

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
    void quickStart(string imageName,double l=numeric_limits<double>::lowest(),double r=numeric_limits<double>::max());

    /**
     * @brief Used when only need to plot single image. After ploting.
     */
    void quickEnd();

private:
    /**
     * @brief Output preamble of a line.
     */
    void linePreamble(string character,double l,double r,bool newLine);

    ofstream file;///< the file to put in.

    string color;///< the color of the line at present.

    NameLibrary colorLibrary;///< offer many sort of colors.
};
