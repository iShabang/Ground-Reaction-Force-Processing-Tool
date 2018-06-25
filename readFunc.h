#ifndef READFUNC_H
#define READFUNC_H
#include <iostream>
#include <fstream>
#include <vector>

void readVector(std::ifstream &input, std::string fileName, std::vector<std::pair<double, double> > &ForcePlate1 /*, std::vector<std::pair<double, double> > &ForcePlate2*/);



std::vector<std::pair<double, double> >* autoRead(std::ifstream &input, std::string fileName, int numTrials);


#endif
