#ifndef READFUNC_H
#define READFUNC_H
#include <iostream>
#include <fstream>
#include <vector>


void readVector(std::ifstream &input, std::string fileName, std::vector<std::pair<double, double> > &ForcePlate1);



void read2Plates(std::ifstream &input, std::string fileName, std::vector<std::pair<double, double> > &ForcePlate1, const int &duration);



std::vector<std::pair<double, double> >* autoRead(std::ifstream &input, int sub, int cond, int numTrials);

void combineVectors(std::vector<std::pair<double,double> > &plate1, std::vector<std::pair<double, double> > &plate2);

#endif
