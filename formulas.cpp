#include <vector>
#include "formulas.h"

//calculate PVA
//creates acc, vel, and pos vectors
void	PVA(std::vector<std::pair<double,double> > &grf, std::vector<std::pair<double,double> > &acc, std::vector<std::pair<double,double> > &vel, std::vector<std::pair<double,double> > &pos){

    double mass, Fg, time;

    //get mass
    mass = calcMass(grf);

    //get Fg
    Fg = calcGravity(mass);

    //initialize time to 1000HZ
    time = .001;

    //initial vector values
    acc.push_back(std::make_pair(grf[0].first,calcAcc(grf[0].second, mass, Fg)));
    vel.push_back(std::make_pair(grf[0].first,calcVel(acc[0].second, grf[0].first, 0)));
    pos.push_back(std::make_pair(grf[0].first,calcPos(vel[0].second, grf[0].first, 0)));

    //build the remaining values and push them onto the vectors
    for(int i=1; i<5000; i++){
	acc.push_back(std::make_pair(grf[i].first,calcAcc(grf[i].second, mass, Fg)));
	vel.push_back(std::make_pair(grf[i].first,calcVel(acc[i].second, time, vel[i-1].second)));
	pos.push_back(std::make_pair(grf[i].first,calcPos(vel[i].second, time, pos[i-1].second)));
    }

}


//Calculate position
//Position = velocity * time 
double calcPos(const double& vel, const double& time, const double& Pi){

    double pos;
    
    pos = (vel * time) + Pi;

    return pos;

}


//Calculate velocity
//velocity = acceleration * time
double calcVel(const double& acc, const double& time, const double& Vi){

    double vel;

    vel = (acc * time) + Vi;

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
double calcMass(const std::vector<std::pair<double, double> > &plateData){

//doubles for mass and Fz
double mass, Fz;
//grab a steady Fz from the beginning
Fz = plateData[50].second;

//divide by 9.81
mass = Fz / 9.81;

return mass;

}
