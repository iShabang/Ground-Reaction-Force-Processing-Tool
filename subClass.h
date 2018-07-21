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
        Subject(int, int, int);               // order of input name, motion, trial
        void createDATfiles();
        void createPVA_DAT();
        void graphAll();
        void avgPeak();
        //void getData()                                        // calls autoRead()
        //double getPVA();                                        // that is being built

    private:
        std::string buildString(int);                                   // victorback <-> victorvert
        std::string buildString(int, int);
        std::string filePrefix;                                          // fileName = string created
        int sub;
        int trials;
        int cond;
        double *peakValues;
};
#endif
