#include <iostream>
#include <vector>
#include "formulas.h"

//Calculate position
//Position = velocity * time 
double calcPos(const double& vel, const double& time){

    double pos;
    
    pos = vel * time;

    return pos;

}


//Calculate velocity
//velocity = acceleration * time
double calcVel(const double& acc, const double& time){

    double vel;

    vel = acc * time;

    return vel;
}


//Calculate acceleration
//acceleration = (Fgrf - Fg)/mass
//Fgrf = Fz from forceplate
//Fg = mass * 9.81 m/s^2
//mass in kg
double calcAcc(const double& Fgrf, const double& mass, const double& Fg){
    
    double acc;

    acc = (Fgrf - Fg)/mass;

    return acc;

}


//Calculate force of gravity
//requires mass
//constant of 9.81 m/s^2
//Fg = mass in kg * 9.81 m/s^2
double calcGravity(const double& mass){
    //double for force of gravity
    double Fg;

    Fg = mass * 9.81;

    return Fg;
    

}


//Calculate mass
//requires Vector to find force in Newtons
double calcMass(std::vector<std::pair<double, double> > &plateData){

//doubles for mass and Fz
double mass, Fz;
//grab a steady Fz from the beginning
Fz = plateData[50].second;

//divide by 9.81
mass = Fz / 9.81;

return mass;

}
