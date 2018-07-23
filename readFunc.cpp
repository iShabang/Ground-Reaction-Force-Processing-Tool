#include <iostream>
#include <fstream>
#include <vector>
#include "readFunc.h"
#include <boost/filesystem.hpp>

#define VEC std::vector<std::pair<double,double> >

/*READ VECTOR
Function reads data from a text file into a vector of pairs (x and y coordinates).
Parameters - input object, file name string, vector of pairs
Function will use the input object to open the given file name
Data will be read from the file into the passed vector
No return value
*/

void buildData(std::string fileName){

    //# of samples
    int samples;

    //create an fstream object for reading
    std::ifstream input;
    std::ofstream output;

    //boost filesystem objects
    boost::filesystem::path p("DAT Files/");
    boost::filesystem::file_status s = status(p);
    if(!boost::filesystem::is_directory(s)){
        boost::filesystem::create_directory(p);
    }

    //String values for reading
    std::string time, Fz1String, Fz2String, garbage, ifileName, ofileName;
 
    ifileName = fileName + ".txt";
    ofileName = fileName + ".dat";

    input.open("Data/" + ifileName);
    if(input.fail())
        std::cout << "input failed!!" << std::endl;
    output.open(p.string() + ofileName);
    if(output.fail())
        std::cout << "output failed!!" << std::endl;

    //skip first 2 lines
    for(int i=0; i<2; i++)
        std::getline(input, garbage);

    //get # of samples
    getline(input, garbage, ':');
    input >> samples;
    
    //Skip the remaining 10 lines of text
    for(int i=0; i<11; i++){
	    std::getline(input, garbage);
    }

    //Read in data points. Loop for number of miliseconds.
    for(int i=0; i<samples; i++){
	getline(input, time, '\t');
	output << time << ' ';

	//grab plate1 fz
	getline(input, Fz1String, '\n');
	output << Fz1String << '\n';

    }

    output.close();

}

/*BUILD DATA 2 PLATES
Reads provided text files with two force plates instead of one.
Function reads the data file, and outputs data into a new file with .dat extension
Parameters
No return value

*/
void buildData2Plates(std::string fileName){

    //# of samples
    int samples, samplesa;

    //create input and output objects for reading and writing
    std::ifstream input;
    std::ofstream output;

    double Fz1, Fz2, T;

    //boost filesystem objects
    boost::filesystem::path p("DAT Files/");
    boost::filesystem::file_status s = status(p);
    if(!boost::filesystem::is_directory(s)){
        boost::filesystem::create_directory(p);
    }


    VEC vecta;
    VEC vectb;

    //String values for reading
    std::string time, Fz1String, Fz2String, garbage;
 
    input.open("Data/" + fileName + ".txt");
    if(input.fail()){
        std::cout << fileName << ".txt failed to open \n";
        return;
    }

    //skip first 2 lines
    for(int i=0; i<2; i++)
        std::getline(input, garbage);

    //get # of samples
    getline(input, garbage, ':');
    input >> samples >> samplesa;
    
    //Skip the remaining 10 lines of text
    for(int i=0; i<11; i++){
	    std::getline(input, garbage);
    }

    //Read in data points. Loop for number of miliseconds.
    for(int i=0; i<samples; i++){
	    getline(input, time, '\t');
        T = std::stod(time);

	    //grab plate1 fz
	    getline(input, Fz1String, '\t');
        Fz1 = std::stod(Fz1String);

	    //grab plate2 fz
	    getline(input, Fz2String, '\n');
        Fz2 = std::stod(Fz2String);

        vecta.push_back(std::make_pair(T, Fz1));
        vectb.push_back(std::make_pair(T, Fz2));

    }
    if(vecta[0].second < 10){
        int timeFound = 0;
        while(vecta[timeFound].second < 10)
            timeFound++;
        combinePlates(fileName, timeFound, samples, vectb, vecta);
    }

    else if(vectb[0].second < 10){
        int timeFound = 0;
        while(vectb[timeFound].second < 10){
            timeFound++;
        }
        combinePlates(fileName, timeFound, samples, vecta, vectb);
    }

}



/*********************************************************************************************
 * Function name:      autoRead
 * Parameters:         which subject, # of conditions, # of trials
 * Return Value:       NONE
 * Purpose:            loops until all data for a subject is read and parsed

*********************************************************************************************/
void autoRead(int sub, int cond, int numTrials){

  std::string trial, subject, condition, fullName;
  int numPlates;

  subject = std::to_string(sub);
  condition = std::to_string(cond);
 
  for(int i=1; i <= numTrials; i++){
    trial = std::to_string(i);
    fullName = "S" + subject + "C" + condition + "T" + trial;
    numPlates = testNumPlates(fullName);
    if(numPlates == 1)
        buildData(fullName);
    else if(numPlates == 2)
        buildData2Plates(fullName);
  } 
  

  return;


}


/*********************************************************************************************
 * Function name:      testNumPlates
 * Parameters:         file name to be opened for testing
 * Return Value:       number of plates captured
 * Purpose:            reads the header of the file passed and determines the number of plates
                       captured

*********************************************************************************************/

int testNumPlates(std::string fileName){
    std::ifstream input;
    std::string garbage;
    char N;
    int numN = 0;
    input.open("Data/" + fileName + ".txt");
    if(!input){
        std::cout << fileName << ".txt failed to open\n";
        return 0;
    }
    for(int i=0; i<12; i++)
        std::getline(input, garbage);
    while(true){
        input >> N;
        if(N == 'N')
            numN++;
        else
            break;
    }
    return numN;
}

/*****************************************************************************************
 * Function Name:   fetchData()
 * Parameters:      name of the file requested, vector to store data
 * Return Type:     Void
 * Purpose:         gets data from the given file and puts it in a vector for processing

*****************************************************************************************/
bool fetchData(std::string fileName, std::vector<std::pair<double, double> > &vect){
    std::ifstream input; 
    double time, force;
    input.open("DAT Files/" + fileName + ".dat");
    if(!input){
        std::cout << fileName << ".dat failed to open\n";
        return true;
    }
    while(!input.eof()){
        input >> time >> force;
        vect.push_back(std::make_pair(time,force));
   }
   input.close();
   return false;
}

/*********************************************************************************************
 * Function name:      combinePlates
 * Parameters:          file name to be created, time found, duration, start vector, end vector 
 * Return Value:       NONE
 * Purpose:            combines two data sets from plates and puts them into one file for 
                       processing

*********************************************************************************************/

void combinePlates(std::string fileName, double timeFound, int duration, VEC &vect1, VEC &vect2){
    std::ofstream output;

    //boost filesystem objects
    boost::filesystem::path p("DAT Files/");
    boost::filesystem::file_status s = status(p);
    if(!boost::filesystem::is_directory(s)){
        boost::filesystem::create_directory(p);
    }

    output.open(p.string() + fileName + ".dat");
    if(output.fail()){
        std::cout << fileName << ".dat failed to open \n";
        return;
    }
    for(int i=0; i<timeFound; i++)
        output << vect1[i].first << ' ' << vect1[i].second << '\n';
    for(int i=timeFound; i<duration; i++)
        output << vect2[i].first << ' ' << vect2[i].second << '\n';
    output.close();
}













