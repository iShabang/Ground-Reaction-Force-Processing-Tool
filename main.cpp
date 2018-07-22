
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
    std::ofstream output;
/*******************************************************************
 * This section will ask for necessary varaibles to create an object
*******************************************************************/

    Subject sub1(1,2,5);
    Subject sub2(2,2,5);
    Subject sub3(3,2,5);

    sub1.createDATfiles();
    sub2.createDATfiles();
    sub3.createDATfiles();

    sub1.createPVA_DAT();
    sub2.createPVA_DAT();
    sub3.createPVA_DAT();

/*
    sub1.graphAll();
    sub2.graphAll();
    sub3.graphAll();
*/

    output.open("AveragePeakValues.txt");

    output << "Average Peak Takeoff GRF" << '\n';
    sub1.avgPeakTakeoff(output);
    sub2.avgPeakTakeoff(output);
    sub3.avgPeakTakeoff(output);
    output << '\n';

    output << "Average Peak GRF" << '\n';
    sub1.avgPeak(output);
    sub2.avgPeak(output);
    sub3.avgPeak(output);
    output << '\n';

    output << "Average Peak Velocity" << '\n';
    sub1.avgPeakVelocity(output);
    sub2.avgPeakVelocity(output);
    sub3.avgPeakVelocity(output);

    output.close();


    return 0;
}
