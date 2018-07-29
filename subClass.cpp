#include "subClass.h"

/*****************************************************************************************
 * Function Name:   Subject - Default Constructor
 * Parameters:      NONE
 * Return Type:     NONE
 * Purpose:         Initializes all private members to their default 
*****************************************************************************************/
Subject::Subject()
{
    sub = 0;
    cond = 0;
    trials = 0;
}

/*****************************************************************************************
 * Function Name:   Subject - constructor with parameters
 * Parameters:      NONE
 * Return Type:     NONE
 * Purpose:         Initializes object with private members assigned to values given in
 *                  parameters.
*****************************************************************************************/
Subject::Subject(int s, int c, int t)
{
    sub = s;
    cond = c;
    trials = t;
    peakValues = new double[c*t];
    peakVelocity = new double[c*t];
    peakTakeoff = new double[c*t];
}

/*****************************************************************************************
 * Function Name:   buildString
 * Parameters:      condition requested
 * Return Type:     String
 * Purpose:         Buids the file name adding two string together. 
 *                  victorvert <-> victorback
*****************************************************************************************/
std::string Subject::buildString(int c)
{
    std::string subject, condition;
    std::string fileName;
    subject = std::to_string(sub);
    condition = std::to_string(c);
    fileName = "S" + subject + "C" + condition + "T"; 
    return fileName;
}

/*****************************************************************************************
 * Function Name:   buildString
 * Parameters:      condition and trial requested
 * Return Type:     String
 * Purpose:         Buids the file name adding two string together. 
 *                  victorvert <-> victorback *****************************************************************************************/
std::string Subject::buildString(int c, int t)
{
    std::string subject, condition, trial;
    std::string fileName;
    subject = std::to_string(sub);
    condition = std::to_string(c);
    trial = std::to_string(t);
    fileName = "S" + subject + "C" + condition + "T" + trial; 
    return fileName;
}



/*****************************************************************************************
 * Function Name:   createDATfiles()
 * Parameters:      NONE
 * Return Type:     Void
 * Purpose:         auto reads all data files associated with the subject
*****************************************************************************************/
void Subject::createDATfiles(){
    int c;
    for(int i=1; i<=cond; i++){
        c = i;
        autoRead(sub, c, trials);
    }
}

/*****************************************************************************************
 * Function Name:   createPVA_DAT()
 * Parameters:      NONE
 * Return Type:     Void
 * Purpose:         calculates PVA for all data sets and outputs the results in a .dat
                    file for graphing
*****************************************************************************************/
void Subject::createPVA_DAT(){
    int index;
    bool noData = false;
    std::string fileName;
    std::vector<std::pair<double, double> > vect;
    for(int i=1; i<=cond; i++){
        for(int j=1; j<=trials; j++){
            index = (i-1) * trials + (j-1);
            fileName = buildString(i,j);
            noData = fetchData(fileName, vect);
            if(noData){
                std::cout << "No data found for " << fileName << "\n";
            }
            else if(!noData){
                peakValues[index] = PVA(fileName, vect, peakVelocity[index], peakTakeoff[index]);
                if(peakValues[index] == 0)
                    return;
                vect.clear();
                vect.shrink_to_fit();
            }
        }
    }
}

/*****************************************************************************************
 * Function Name:   graphAll()
 * Parameters:      NONE
 * Return Type:     Void
 * Purpose:         creats graph postscripts for all data files

*****************************************************************************************/
void Subject::graphAll(){
    Gnuplot gp;
    std::string fileName;

    //boost filesystem objects
    boost::filesystem::path p("Graphs/");
    boost::filesystem::path test;
    boost::filesystem::file_status s = status(p);
    if(!boost::filesystem::is_directory(s)){
        boost::filesystem::create_directory(p);
    }

    for(int i=1; i<=cond; i++){
        for(int j=1; j<=trials; j++){
            fileName = buildString(i,j);
            test = "DAT Files/" + fileName + ".dat";
            s = status(test);
            if(!boost::filesystem::exists(s)){
                std::cout << "Graph data for " << fileName << " does not exist\n";
            }
            else{
                gp << "set term postscript eps enhanced 'arial_bold' 12 \n";
                gp << "unset key \n";
                gp << "set grid \n";
                gp << "set xlabel 'Time (seconds)' \n";

                gp << "set ylabel 'Newtons' \n";
                gp << "set title '" << fileName << " GRF vs Time'\n";
                gp << "set output '" << p.string() + fileName + ".eps'" << "\n";
                gp << "plot [:] [:7000] '" << "DAT Files/" + fileName + ".dat" << "'\n";


                gp << "set ylabel 'Position (Meters)' \n";
                gp << "set title '" << fileName << " Position vs Time' \n";
                gp << "set output '" << p.string() +  fileName + "P.eps'" << "\n";
                gp << "plot '" << "Results/" + fileName + "P.dat" << "'\n";

                gp << "set ylabel 'Velocity (M/s)' \n";
                gp << "set title '" << fileName << " Velocity vs Time' \n";
                gp << "set output '" << p.string() + fileName + "V.eps'" << "\n";
                gp << "plot '" << "Results/" + fileName + "V.dat" << "'\n";

                gp << "set ylabel 'Acceleration (M/s^2)' \n";
                gp << "set title '" << fileName << " Acceleration vs Time' \n";
                gp << "set output '" << p.string() + fileName + "A.eps'" << "\n";
                gp << "plot '" << "Results/" + fileName + "A.dat" << "'\n";
            }

        }
    }
}

/*****************************************************************************************
 * Function Name:   avgPeak()
 * Parameters:      NONE
 * Return Type:     Void
 * Purpose:         finds the average peak values for all conditions

*****************************************************************************************/
void Subject::avgPeak(std::ofstream& output){
    bool close = false;
    double sum, avg;
    int index;

    //boost filesystem objects
    boost::filesystem::path p("Results/Averages/");
    boost::filesystem::file_status s = status(p);
    if(!boost::filesystem::is_directory(s)){
        boost::filesystem::create_directory(p);
    }

    if(!output.is_open()){
        output.open(p.string() + "Average Peak Landing Force.txt", std::ofstream::app);
        close = true;
    }

    for(int i=0; i<cond; i++){
        sum = 0;
        for(int j=0; j<trials; j++){
            index = i * trials + j;
            sum = sum + peakValues[index];
        }
        avg = sum / (double)trials;
        output << "S" << sub << "C" << i+1 << '\t' << avg << "\n";
    }
    if(close)
        output.close();
    return;
}

/*****************************************************************************************
 * Function Name:   avgPeakVelocity()
 * Parameters:      NONE
 * Return Type:     Void
 * Purpose:         finds the average peak velocity for all conditions

*****************************************************************************************/

void Subject::avgPeakVelocity(std::ofstream& output){
    bool close = false;
    double sum, avg;
    int index;

    //boost filesystem objects
    boost::filesystem::path p("Results/Averages/");
    boost::filesystem::file_status s = status(p);
    if(!boost::filesystem::is_directory(s)){
        boost::filesystem::create_directory(p);
    }

    if(!output.is_open()){
        output.open(p.string() + "Average Peak Velocity.txt", std::ofstream::app);
        close = true;
    }
    for(int i=0; i<cond; i++){
        sum = 0;
        for(int j=0; j<trials; j++){
            index = i * trials + j;
            sum = sum + peakVelocity[index];
        }
        avg = sum / (double)trials;
        output << "S" << sub << "C" << i+1 << '\t' << avg << "\n";
    }
    if(close)
        output.close();
    return;
}

/*****************************************************************************************
 * Function Name:   avgPeakTakeoff()
 * Parameters:      NONE
 * Return Type:     Void
 * Purpose:         finds the average peak takeoff force for all conditions

*****************************************************************************************/

void Subject::avgPeakTakeoff(std::ofstream& output){
    bool close = false;
    double sum, avg;
    int index;

    //boost filesystem objects
    boost::filesystem::path p("Results/Averages/");
    boost::filesystem::file_status s = status(p);
    if(!boost::filesystem::is_directory(s)){
        boost::filesystem::create_directory(p);
    }

    if(!output.is_open()){
        output.open(p.string() + "Average Maximum Force During Jump Phase.txt", std::ofstream::app);
        close = true;
    }
    for(int i=0; i<cond; i++){
        sum = 0;
        for(int j=0; j<trials; j++){
            index = i * trials + j;
            sum = sum + peakTakeoff[index];
        }
        avg = sum / (double)trials;
        output << "S" << sub << "C" << i+1 << '\t' << avg << "\n";
    }
    if(close)
        output.close();
    return;
}

