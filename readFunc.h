#ifndef READFUNC_H
#define READFUNC_H
#include <iostream>
#include <fstream>
#include <vector>


void readVector(std::string fileName, std::vector<std::pair<double, double> > &ForcePlate1, int duration);



void read2Plates(std::string fileName, std::vector<std::pair<double, double> > &plate1, std::vector<std::pair<double, double> > &plate2, const int &duration);

std::vector<std::pair<double, double> >* autoRead(int sub, int cond, int numTrials, int duration);

std::vector<std::pair<double, double> >* autoRead2Plates(int sub, int cond, int numTrials, int duration);

void combineVectors(std::vector<std::pair<double,double> > &plate1, std::vector<std::pair<double, double> > &plate2);

#endif
