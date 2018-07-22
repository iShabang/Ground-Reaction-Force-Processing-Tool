#include <vector>
#include <fstream>
#include "formulas.h"

/*calculate PVA
Function calculates the PVA of the data passed in and outputs the data into separate .dat files for Position, Velocity, and Acceleration
parameters:
	grf - vector containing ground reaction force vs time

*/
double PVA(std::string fileName, std::vector<std::pair<double,double> > &grf, double& peakVelocity){

    std::ofstream output1, output2, output3;

    double mass, Fg, time, Vi, Pi, pos, vel, acc, peak;

    //create file names
    std::string posDat, velDat, accDat;
    posDat = "Results/" + fileName + "P.dat";
    velDat = "Results/" + fileName + "V.dat";
    accDat = "Results/" + fileName + "A.dat";

    //open files
    output1.open(posDat);
    if(!output1){
        std::cout << posDat << " failed to open. Aborting." << std::endl;
        return 0;
    }
    output2.open(velDat);
    if(!output2){
        std::cout << velDat << " failed to open. Aborting." << std::endl;
        return 0;
    }
    output3.open(accDat);
    if(!output3){
        std::cout << accDat << " failed to open. Aborting." << std::endl;
        return 0;
    }

    //get mass
    mass = calcMass(grf);

    //get Fg (force of gravity)
    Fg = calcGravity(mass);

    //initialize time to 1000HZ
    time = .001;

    //initialize pos and vel
    vel = 0;
    pos = 0;

    //initialize peak to first value
    peak = grf[0].second;
    peakVelocity = vel;

    //calculate values and output to file
    for(int i=0; i<grf.size(); i++){
        Vi = vel;
        Pi = pos;
    if(grf[i].second > peak)
        peak = grf[i].second;
	acc = calcAcc(grf[i].second, mass, Fg);
	vel = calcVel(acc, time, Vi);
    if(vel > peakVelocity)
        peakVelocity = vel;
	pos = calcPos(vel, time, Pi);

	output1 << grf[i].first << ' ' << pos << '\n';
	output2 << grf[i].first << ' ' << vel << '\n';
	output3 << grf[i].first << ' ' << acc << '\n';
        
    }

    output1.close();
    output2.close();
    output3.close();

    return peak;

}


//Calculate position
//Position = velocity * time + initial position 
double calcPos(const double& vel, const double& time, const double& Pi){

    double pos;
    
    pos = (vel * time) + Pi;

    return pos;

}


//Calculate velocity
//velocity = acceleration * time + initial velocity
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
//mass = baseline ground reaction force / 9.81
double calcMass(const std::vector<std::pair<double, double> > &plateData){

//doubles for mass and Fz
double mass, Fz;
//grab a steady Fz from the beginning
Fz = plateData[50].second;

//divide by 9.81
mass = Fz / 9.81;

return mass;

}
