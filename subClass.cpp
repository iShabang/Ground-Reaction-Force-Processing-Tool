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
 *                  victorvert <-> victorback
*****************************************************************************************/
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
    std::string fileName;
    std::vector<std::pair<double, double> > vect;
    for(int i=1; i<=cond; i++){
        for(int j=1; j<=trials; j++){
            fileName = buildString(i,j);
            fetchData(fileName, vect);
            PVA(fileName, vect);
            vect.clear();
            vect.shrink_to_fit();
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
    for(int i=1; i<=cond; i++){
        for(int j=1; j<=trials; j++){
            fileName = buildString(i,j);
            gp << "set term postscript eps enhanced 'arial' 12 \n";
            gp << "set output '" << "Graphs/" + fileName + ".eps'" << "\n";
            gp << "plot '" << "Results/" + fileName + ".dat" << "'\n";
            gp << "set output '" << "Graphs/" + fileName + "P.eps'" << "\n";
            gp << "plot '" << "Results/" + fileName + "P.dat" << "'\n";
            gp << "set output '" << "Graphs/" + fileName + "V.eps'" << "\n";
            gp << "plot '" << "Results/" + fileName + "V.dat" << "'\n";
            gp << "set output '" << "Graphs/" + fileName + "A.eps'" << "\n";
            gp << "plot '" << "Results/" + fileName + "A.dat" << "'\n";
        }
    }
}


