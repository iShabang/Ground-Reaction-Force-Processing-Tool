
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
    std::ifstream input;
    Gnuplot gp;

/*******************************************************************
 * This section will ask for necessary varaibles to create an object
*******************************************************************/
    std::cout << "Welcome to the force platform data collection program." << std::endl;
	std::cout << "We will ask you to fill out a couple of inputs to continue with our program." << std::endl;

    Subject sub1(1,2,5);
    Subject sub2(2,2,5);
    Subject sub3(3,2,5);

    sub1.createDATfiles();
    sub2.createDATfiles();
    sub3.createDATfiles();

    sub1.createPVA_DAT();
    sub2.createPVA_DAT();
    sub3.createPVA_DAT();

    sub1.graphAll();
    sub2.graphAll();
    sub3.graphAll();

    sub1.avgPeak();
    sub2.avgPeak();
    sub3.avgPeak();

    return 0;
}
