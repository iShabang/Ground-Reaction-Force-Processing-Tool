#include <vector>
#include <fstream>
#include "formulas.h"
#include <boost/filesystem.hpp>

/*calculate PVA
Function calculates the PVA of the data passed in and outputs the data into separate .dat files for Position, Velocity, and Acceleration
parameters:
	grf - vector containing ground reaction force vs time

*/
double PVA(std::string fileName, std::vector<std::pair<double,double> > &grf, double& peakVelocity, double& peakTakeoff){
    

    std::ofstream output1, output2, output3;

    bool takeoff = true;
    double mass, Fg, time, Vi, Pi, pos, vel, acc, peak;

    //boost filesystem objects
    boost::filesystem::path p("Results/");
    boost::filesystem::file_status s = status(p);
    if(!boost::filesystem::is_directory(s)){
        boost::filesystem::create_directory(p);
    }

    //create file names
    std::string posDat, velDat, accDat;
    posDat = p.string() + fileName + "P.dat";
    velDat = p.string() + fileName + "V.dat";
    accDat = p.string() + fileName + "A.dat";

    //open files
    output1.open(posDat);
    if(output1.fail()){
        std::cout << posDat << " failed to open. Aborting." << std::endl;
        return 0;
    }
    output2.open(velDat);
    if(output2.fail()){
        std::cout << velDat << " failed to open. Aborting." << std::endl;
        return 0;
    }
    output3.open(accDat);
    if(output3.fail()){
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
    peakTakeoff = grf[0].second;
    peakVelocity = vel;

    //calculate values and output to file
    for(int i=0; i<grf.size(); i++){
        Vi = vel;
        Pi = pos;
    if(grf[i].second > peak)
        peak = grf[i].second;
    if(takeoff && grf[i].second > 1 && grf[i].second > peakTakeoff){
        peakTakeoff = grf[i].second; 
    }
    else if(grf[i].second <= 1)
        takeoff = false;
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
