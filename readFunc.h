#ifndef READFUNC_H
#define READFUNC_H
#include <iostream>
#include <fstream>
#include <vector>

#define VEC std::vector<std::pair<double,double> >

void buildData(std::string fileName, int duration);

void buildData2Plates(std::string fileName, const int &duration);

void autoRead(int sub, int cond, int numTrials, int duration);

void autoRead2Plates(int sub, int cond, int numTrials, int duration);

int testNumPlates(std::string);

void fetchData(std::string, std::vector<std::pair<double, double> > &);

void combinePlates(std::string, double, int, VEC &, VEC &);

#endif
