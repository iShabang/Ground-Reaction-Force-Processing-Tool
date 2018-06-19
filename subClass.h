#ifndef SUBCLASS_H
#define SUBCLASS_H
#include <vector>
#include <fstream>
#include <iostream>
#include <string>
#include <iomanip>
#include "gnuplot-iostream.h"
#include "readFunc.h"
#include "formulas.h"

class Subject
{
    public:
        Subject();
        Subject(std::string , std::string , int);               // order of input name, motion, trial
        void readInData()                                       // calls read function
        double getPVA();                                        // that is being built

    private:
        std::string name, motion;                               // String Variables for name and type of motion
        int trials;
        std::vector<std::pair<double, double> > *backTucks;     // Array of vectors dynamically allocated.
        std::vector<std::pair<double, double> > *vertJumps;     // Array of vectors dynamically allocated.
};
#endif
