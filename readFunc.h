#ifndef READFUNC_H
#define READFUNC_H
#include <iostream>
#include <fstream>
#include <vector>

#define VEC std::vector<std::pair<double,double> >

void buildData(std::string fileName);

void buildData2Plates(std::string fileName);

void autoRead(int sub, int cond, int numTrials);

int testNumPlates(std::string);

void fetchData(std::string, std::vector<std::pair<double, double> > &);

void combinePlates(std::string, double, int, VEC &, VEC &);

#endif
