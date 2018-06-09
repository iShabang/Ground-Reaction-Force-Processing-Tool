/*Read in Data
Program opens the data file, reads in time, Plate1 FZ, and Plate2 Fz
Need to convert to function
Need to transfer data to an object 
*/

#include <iostream>
#include <fstream>

int main(){

    //Input variable
    std::ifstream input;

    //String values for reading
    std::string time, plate1, plate2, garbage;
    

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

    }

    input.close();

    return 0;
}
