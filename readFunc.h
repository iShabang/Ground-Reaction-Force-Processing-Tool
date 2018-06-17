#ifndef READFUNC_H
#define READFUNC_H
#include <iostream>
#include <fstream>
#include <vector>

void readVector(std::ifstream &input, std::vector<std::pair<double, double> > &ForcePlate1, std::vector<std::pair<double, double> > &ForcePlate2);
#endif
