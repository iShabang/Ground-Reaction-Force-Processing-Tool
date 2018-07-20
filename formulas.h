#ifndef FORMULAS_H
#define FORMULAS_H
#include <iostream>
#include <vector>

//calculate pva
double PVA(std::string fileName, std::vector<std::pair<double,double> > &grf);

//Calculate position
double calcPos(const double& vel, const double& time, const double& Pi);


//Calculate velocity
double calcVel(const double& acc, const double& time, const double& Vi);


//Calculate acceleration
//acceleration = (Fgrf - Fg)/mass
//Fgrf = Fz from forceplate
//Fg = mass * 9.81 m/s^2
//mass in kg
double calcAcc(const double& Fgrf, const double& mass, const double& Fg);


//Calculate force of gravity
//requires mass
//constant of 9.81 m/s^2
//Fg = mass in kg * 9.81 m/s^2
double calcGravity(const double& mass);

//Calculate mass
//requires Vector to find force in Newtons
double calcMass(const std::vector<std::pair<double, double> > &plateData);

#endif
