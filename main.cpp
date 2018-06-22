
#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include "gnuplot-iostream.h"
#include "readFunc.h"
#include "formulas.h"
#include "subClass.h"

int main()
{
    int dataSize = 10000;
    double mass, Fg;
    std::ifstream input;
    Gnuplot gp;
    Subject *sub;

/*******************************************************************
 * This section will ask for necessary varaibles to create an object
*******************************************************************/
    std::cout << "Welcome to the force platform data collection program." << std::endl;
    std::cout << "We will ask you to fill out a couple of inputs to continue with our program." << std::endl;



    //Create vectors
    std::vector<std::pair<double, double> > plate1;
    std::vector<std::pair<double, double> > plate2;
    std::vector<std::pair<double, double> > acc;
    std::vector<std::pair<double, double> > vel;
    std::vector<std::pair<double, double> > pos;


    //Read data into vectors
    readVector(input, plate1, plate2);

    //get mass
    mass = calcMass(plate1);

    //get Fg
    Fg = calcGravity(mass);

    //calculate PVA
    for(int i=0; i<5000; i++){
	acc.push_back(std::make_pair(plate1[i].first,calcAcc(plate1[i].second, mass, Fg)));
	vel.push_back(std::make_pair(plate1[i].first,calcVel(acc[i].second, plate1[i].first)));
	pos.push_back(std::make_pair(plate1[i].first,calcPos(vel[i].second, plate1[i].first)));
    }




    //Print out DarkGrey
   /* std::cout << std::right << std::fixed << std::setprecision(6);
    for(int i=0; i<5000; i++){
	std::cout << "x = " << plate1[i].first << "\ty = " << plate1[i].second << std::endl;
    }
*/

    gp << "set terminal wxt 1" << std::endl;
    gp << "plot" << gp.file1d(plate1) << "with lines title 'plate1'" << std::endl; 

    gp << "set terminal wxt 2" << std::endl;
    gp << "plot" << gp.file1d(acc) << "with lines title 'acc'" << std::endl; 

    gp << "set terminal wxt 3" << std::endl;
    gp << "plot" << gp.file1d(vel) << "with lines title 'vel'" << std::endl; 

    gp << "set terminal wxt 4" << std::endl;
    gp << "plot" << gp.file1d(pos) << "with lines title 'pos'" << std::endl; 



    return 0;
}
