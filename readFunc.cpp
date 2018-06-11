
#include <iostream>
#include <fstream>
#include <vector>

/*Function reads the data file, converts the strings to doubles, and pushes the data into the corresponding vectors
Parameters
  &input - address of the input file
  &DarkGrey - address of the DarkGrey vector. Holds x and y coordinates. 
  &LightGrey - address of the LightGrey plate vector. Holds x and y coordinates.
No return value
Need to create string parameter for file name.
*/
void readVector(std::ifstream &input, std::vector<std::pair<double, double> > &DarkGrey, std::vector<std::pair<double, double> > &LightGrey){

    //String values for reading
    std::string time, plate1, plate2, garbage;

    //Double values after conversion
    double t, p1, p2;

    input.open("testData");

    //Skip the first 13 lines of text
    for(int i=0; i<13; i++){
	    std::getline(input, garbage);
    }

    //Read in data points. Loop for number of miliseconds.
    for(int i=0; i<5000; i++){
	getline(input, time, '\t');

	//Skip plate1 fx & fy
	getline(input, garbage, '\t');
	getline(input, garbage, '\t');

	//grab plate1 fz
	getline(input, plate1, '\t');

	//skip plate2 fx & fy
	getline(input, garbage, '\t');
	getline(input, garbage, '\t');

	//grab plate2 fz
	getline(input, plate2, '\n');

	//convert strings to doubles
	t = std::stod(time);
	p1 = std::stod(plate1);
	p2 = std::stod(plate2);

	//move values into vectors
	DarkGrey.push_back(std::make_pair(t,p1));
	LightGrey.push_back(std::make_pair(t,p2));

    }

    input.close();

}
