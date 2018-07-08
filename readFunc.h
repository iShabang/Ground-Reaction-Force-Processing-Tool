#ifndef READFUNC_H
#define READFUNC_H
#include <iostream>
#include <fstream>
#include <vector>


void buildData(std::string fileName, int duration);

void buildData2Plates(std::string fileName, const int &duration);

void autoRead(int sub, int cond, int numTrials, int duration);

void autoRead2Plates(int sub, int cond, int numTrials, int duration);

#endif
