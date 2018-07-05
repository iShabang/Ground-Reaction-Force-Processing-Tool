#include <iostream>
#include <fstream>
#include <vector>
#include "readFunc.h"


/*READ VECTOR
Function reads data from a text file into a vector of pairs (x and y coordinates).
Parameters - input object, file name string, vector of pairs
Function will use the input object to open the given file name
Data will be read from the file into the passed vector
No return value
*/

void readVector(std::ifstream &input, std::string fileName, std::vector<std::pair<double, double> > &ForcePlate1){

    //String values for reading
    std::string time, Fz1String, Fz2String, garbage;
 
    //Character value for testing input
    char test, a;

    //number of data columns
    int dataColumns=0;

    //Double values after conversion
    double t, Fz1, Fz2;

    input.open(fileName);

    //Skip the first 13 lines of text
    for(int i=0; i<13; i++){
	    std::getline(input, garbage);
    }

    //Read in data points. Loop for number of miliseconds.

    for(int i=0; i<5000; i++){
	getline(input, time, '\t');
//	std::cout << "time = " << time << "\t";
	//std::cin.get();


	//Skip plate1 fx & fy
//	getline(input, garbage, '\t');
//	getline(input, garbage, '\t');

	//grab plate1 fz
	getline(input, Fz1String, '\n');
//	std::cout << "fz = " << Fz1String << std::endl;
	//std::cin.get();

	//convert strings to doubles
	t = std::stod(time);
	Fz1 = std::stod(Fz1String);

	//move values into vectors
	ForcePlate1.push_back(std::make_pair(t,Fz1));

    }

    input.close();

}

/*Overloaded readVector to incorporate two force plates instead of one. Need to find a way to add the two sets
of data together to create one vector
Function reads the data file, converts the strings to doubles, and pushes the data into the corresponding vectors
Parameters
  &input - address of the input file
  &ForcePlate1 - address of the first force plate vector. Holds x and y coordinates. 
  &ForcePlate2 - address of the second force plate vector. Holds x and y coordinates.
No return value

*/
void read2Plates(std::ifstream &input, std::string fileName, std::vector<std::pair<double, double> > &plate1, const int &duration){

    //String values for reading
    std::string time, Fz1String, Fz2String, garbage;
 
    //Character value for testing input
    char test, a;

    //number of data columns
    int dataColumns=0;

    //Double values after conversion
    double t, Fz1, Fz2;

    //Create a second vector. They will be combined after the data is read.
    std::vector<std::pair<double, double> > plate2;

    //small integer for 

    input.open(fileName);

    //Skip the first 13 lines of text
    for(int i=0; i<13; i++){
	    std::getline(input, garbage);
    }



    //Read in data points. Loop for number of miliseconds.
    for(int i=0; i<duration; i++){
	getline(input, time, '\t');
	std::cout << "time = " << time << std::endl;
//	std::cin.get();



	//grab plate1 fz
	getline(input, Fz1String, '\t');

	//convert strings to doubles
	t = std::stod(time);
	Fz1 = std::stod(Fz1String);

	//move values into vectors
	plate1.push_back(std::make_pair(t,Fz1));
	

	//grab plate2 fz
	getline(input, Fz2String, '\n');

	//convert string to double
	Fz2 = std::stod(Fz2String);

	//move values into vectors
	plate2.push_back(std::make_pair(t,Fz2));
	
    }

    input.close();

    combineVectors(plate1, plate2);

}




/*AUTO READ FUNCTION
1. Function will take in a string consisting of "Name" + "movement".
Using an index, we will add a number to the end of the string.
This will be a filename (file must exist and number of files must be known)
example: let i = 3, name = "Shaun", movment = "VertJump"
convert i to character "3"
add strings together to form "ShaunVertJump3"

2. reads data using readVector

3. loop until all files are read (until i = # of files)

*/

std::vector<std::pair<double, double> >* autoRead(std::ifstream &input, int sub, int cond, int numTrials){

  std::vector<std::pair<double, double> >* dataVectors = new std::vector<std::pair<double, double> >[numTrials];

  std::string trial, subject, condition, fullName;

  subject = std::to_string(sub);
  condition = std::to_string(cond);
 

  for(int i=1; i <= numTrials; i++){
    trial = std::to_string(i);
    fullName = "S" + subject + "C" + condition + "T" + trial + ".txt";
    readVector(input, fullName, dataVectors[i-1]);
  } 

  return dataVectors;


}



/*COMBINE VECTORS
function will take data from two force plates and add them together to create one vector for graphing. 
Current implimentation: add y values together. This method will cause some inaccuracy due to the impact forces from the landing. Some of the force will dissapate to the neighboring plate.
No return value. All operations occur on the first vector passed in. 

*/
void combineVectors(std::vector<std::pair<double,double> > &plate1, std::vector<std::pair<double, double> > &plate2){
  int size = plate1.size();
  for(int i=0; i<size; i++){
    plate1[i].second = plate1[i].second + plate2[i].second;

  }


}






