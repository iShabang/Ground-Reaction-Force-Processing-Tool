#include <iostream>
#include <fstream>
#include <vector>
#include "readFunc.h"

/*Function reads the data file, converts the strings to doubles, and pushes the data into the corresponding vectors
Parameters
  &input - address of the input file
  &ForcePlate1 - address of the first force plate vector. Holds x and y coordinates. 
  &ForcePlate2 - address of the second force plate vector. Holds x and y coordinates.
No return value

Need to create string parameter for file name.
*/
void readVector(std::ifstream &input, std::vector<std::pair<double, double> > &ForcePlate1, std::vector<std::pair<double, double> > &ForcePlate2){

    //String values for reading
    std::string time, Fz1String, Fz2String, garbage;
 
    //Character value for testing input
    char test, a;

    //number of data columns
    int dataColumns=0;

    //Double values after conversion
    double t, Fz1, Fz2;

    //small integer for 

    input.open("testData");

    //Skip the first 13 lines of text
    for(int i=0; i<12; i++){
	    std::getline(input, garbage);
    }

    //read in characters one at a time until LF is read.
    //if the number of Ns = 3, read in one plate
    //if the number of Ns = 6, read in two pates

    while(true){
    //read in first character

    //the get function is an unformatted read, which allows it to retrieve blank space. the ">> "operator is 
    //formatted, and skips over /n and /t
	input.get(test);
	//std::cout << test << std::endl
	//std::cin >> a;
    //if character = N, increment
	if(test == 'N'){
	    dataColumns++;
	    //std::cout << "dataColumns = " << dataColumns << std::endl;
	}
    //if character = LF, end loop
	else if(test == '\n'){
	    //std::cout << "test = LF" << std::endl;
	    break;
	}

    //else loop again
    }

/*design another loop to incorporate 3 columns instead of 6, or somehow implement a way to use
the same loop and adjust using variables

Possible solution 1: use a for loop, set index to dataColumns, divide index by 3 each time,
and test if index is greater than 1. If the index is 3 and you divide it by 3, the result would be 1,
therefore it would only need to grab one plate worth of data on each line. This will scale with any number of plates used.

Possible soluton 2: use an if statement in the loop to test for the number of data columns. If there are ever
more than two force plates, this could be a cumbersome and inefficient method. It will work for a small number
of plates. 

Possible solution 3: create separate functions for different number of plates. 
*/



    //Read in data points. Loop for number of miliseconds.
    //Using solution 2
    for(int i=0; i<5000; i++){
	getline(input, time, '\t');
//	std::cout << "time = " << time << std::endl;
//	std::cin.get();


	//Skip plate1 fx & fy
	getline(input, garbage, '\t');
	getline(input, garbage, '\t');

	//grab plate1 fz
	//if only 1 plate, there will be a \n at the end
	// if 2 plates, there will be a \t at this point
	if(dataColumns == 3)
	    getline(input, Fz1String, '\n');
	else
	    getline(input, Fz1String, '\t');
//	std::cout << "fz = " << Fz1String << std::endl;
//	std::cin.get();

	//convert strings to doubles
	t = std::stod(time);
	Fz1 = std::stod(Fz1String);

	//move values into vectors
	ForcePlate1.push_back(std::make_pair(t,Fz1));
	
	//if # of columns = 6, then read in another plate for the current line.
	if(dataColumns==6){

	    //skip plate2 fx & fy
	    getline(input, garbage, '\t');
	    getline(input, garbage, '\t');

	    //grab plate2 fz
	    getline(input, Fz2String, '\n');

	    //convert string to double
	    Fz2 = std::stod(Fz2String);

	    //move values into vectors
	    ForcePlate2.push_back(std::make_pair(t,Fz2));
	}

    }

    input.close();

}
