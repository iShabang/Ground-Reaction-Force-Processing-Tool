#include <vector>
#include <fstream>
#include "formulas.h"

/*calculate PVA
Function calculates the PVA of the data passed in and outputs the data into separate .dat files for Position, Velocity, and Acceleration
parameters:
	grf - vector containing ground reaction force vs time

*/
void	PVA(std::string fileName, std::vector<std::pair<double,double> > &grf){

    std::ofstream output1, output2, output3;

    double mass, Fg, time, Vi, Pi, pos, vel, acc;

    //create file names
    std::string posDat, velDat, accDat;
    posDat = fileName + "P.dat";
    velDat = fileName + "V.dat";
    accDat = fileName + "A.dat";

    //open files
    output1.open(posDat);
    std::cout << "opening " << fileName << "P.dat" << std::endl;
    output2.open(velDat);
    std::cout << "opening " << fileName << "V.dat" << std::endl;
    output3.open(accDat);
    std::cout << "opening " << fileName << "A.dat" << std::endl;

    //get mass
    mass = calcMass(grf);

    //get Fg (force of gravity)
    Fg = calcGravity(mass);

    //initialize time to 1000HZ
    time = .001;

    //initialize pos and vel
    vel = 0;
    pos = 0;

    //calculate values and output to file
    for(int i=0; i<grf.size(); i++){
        Vi = vel;
        Pi = pos;
	
	acc = calcAcc(grf[i].second, mass, Fg);
	vel = calcVel(acc, time, Vi);
	pos = calcPos(vel, time, Pi);

	output1 << grf[i].first << ' ' << pos << '\n';
	output2 << grf[i].first << ' ' << vel << '\n';
	output3 << grf[i].first << ' ' << acc << '\n';
        
    }

    output1.close();
    std::cout << "closing " << fileName << "P.dat" << std::endl;
    output2.close();
    std::cout << "closing " << fileName << "V.dat" << std::endl;
    output3.close();
    std::cout << "closing " << fileName << "A.dat" << std::endl;
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
