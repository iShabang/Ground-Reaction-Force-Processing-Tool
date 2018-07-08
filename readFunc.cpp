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

void buildData(std::string fileName, int duration){

    //create an fstream object for reading
    std::ifstream input;
    std::ofstream output;

    //String values for reading
    std::string time, Fz1String, Fz2String, garbage, ifileName, ofileName;
 
    ifileName = fileName + ".txt";
    ofileName = fileName + ".dat";

    input.open(ifileName);
    output.open(ofileName);

    //Skip the first 13 lines of text
    for(int i=0; i<13; i++){
	    std::getline(input, garbage);
    }

    //Read in data points. Loop for number of miliseconds.
    for(int i=0; i<duration; i++){
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
void buildData2Plates(std::string fileName, const int &duration){

    //create input and output objects for reading and writing
    std::ifstream input;
    std::ofstream output;

    //String values for reading
    std::string time, Fz1String, Fz2String, garbage, ifileName, ofileName;
 
    ifileName = fileName + ".txt";
    ofileName = fileName + ".dat";

    input.open(ifileName);
    output.open(ofileName);
    

    //Skip the first 13 lines of text
    for(int i=0; i<13; i++){
	    std::getline(input, garbage);
    }

    //Read in data points. Loop for number of miliseconds.
    for(int i=0; i<duration; i++){
	getline(input, time, '\t');
	output << time << ' ';

	//grab plate1 fz
	getline(input, Fz1String, '\t');
	output << Fz1String << ' ';

	//grab plate2 fz
	getline(input, Fz2String, '\n');
	output << Fz2String << '\n';

    }

    output.close(); 


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

void autoRead(int sub, int cond, int numTrials, int duration){

  std::string trial, subject, condition, fullName;

  subject = std::to_string(sub);
  condition = std::to_string(cond);
 
  for(int i=1; i <= numTrials; i++){
    trial = std::to_string(i);
    fullName = "S" + subject + "C" + condition + "T" + trial;
    buildData(fullName, duration);
  } 
  

  return;


}






/*AUTO READ 2 PLATES
Function reads in all data for subject that used two force platforms
Each trial will yield two separate vectors

*/
void autoRead2Plates(int sub, int cond, int numTrials, int duration){

  std::string trial, subject, condition, fullName;

  subject = std::to_string(sub);
  condition = std::to_string(cond);
 
  int j = 0;  

  for(int i=1; i < numTrials*2; i = i+2){
    j = i/2 + 1;
    trial = std::to_string(j);
    fullName = "S" + subject + "C" + condition + "T" + trial;
    std::cout << "reading " << fullName << std::endl;
    buildData2Plates(fullName, duration);
  } 

  return;

}















