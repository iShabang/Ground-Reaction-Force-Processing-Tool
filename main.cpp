
#include <iostream>
#include <fstream>
#include "subClass.h"
#include <stdlib.h>

void printMainMenu();
void inputData(Subject **, int);
void calculations(Subject **, int);
void graphing(Subject **, int);

int main()
{
    std::ofstream output;
/*******************************************************************
 * This section will ask for necessary varaibles to create an object
*******************************************************************/

    Subject **subjects; 
    int choice = 1, numSub, numCond, numTrials;

    std::cout << "Enter number of subjects: "; std::cin >> numSub;
    std::cout << "Enter number of conditions: "; std::cin >> numCond;
    std::cout << "Enter number of trials: "; std::cin >> numTrials;

    subjects = new Subject*[numSub];
    for(int i=0; i<numSub; i++){
        subjects[i] = new Subject(i+1, numCond, numTrials);
    }

    while(choice != 4){
        system("clear");
        printMainMenu();
        std::cin >> choice;
        switch (choice){
            case 1: inputData(subjects, numSub);
                    break;
            case 2: calculations(subjects, numSub);
                    break;
            case 3: graphing(subjects, numSub);
                    break;
            case 4: break;
        }
        
        
    }

    /*

    //boost filesystem objects
    boost::filesystem::path p("Data/");
    boost::filesystem::file_status s = status(p);
    if(!boost::filesystem::is_directory(s)){
        boost::filesystem::create_directory(p);
    }
    std::cout << "Please make sure all data is in Data/. Press enter to continue ... ";
    std::cin.get();


    p = "Results/Averages/";
    s = status(p);
    if(!boost::filesystem::is_directory(s))
        boost::filesystem::create_directory(p);

    output.open(p.string() + "AveragePeakValues.txt");

    output << "Average Peak Takeoff GRF" << '\n';
    output << '\n';

    output << "Average Peak GRF" << '\n';
    output << '\n';

    output << "Average Peak Velocity" << '\n';

    output.close();
    */


    system("clear");
    return 0;
}


void printMainMenu(){
    std::cout << "1. Input Data \n";
    std::cout << "2. Calculations \n";
    std::cout << "3. Graphing \n";
    std::cout << "4. Exit \n";
}

void inputData(Subject **subjects, int numSub){

    //boost filesystem objects
    boost::filesystem::path p("Data/");
    boost::filesystem::file_status s = status(p);
    if(!boost::filesystem::is_directory(s)){
        boost::filesystem::create_directory(p);
    }
    system("clear");
    std::cout << "Please make sure all data is in Data/. Press enter to continue ... ";
    std::cin.ignore();
    std::cin.get();

    int choice = 0;
    while(choice != 3){
        //system("clear");
        std::cout << "1. Input All Subjects \n";
        std::cout << "2. Input One Subject \n";
        std::cout << "3. Previous Menu... \n";
        std::cin >> choice;
        switch(choice){
            case 1:
                for(int i=0; i<numSub; i++){
                    subjects[i]->createDATfiles();
                }
            case 3: break;
            default: std::cout << "Please enter a valid option \n";
        }
    }
}


void calculations(Subject **subjects, int numSub){
    int choice = 0;
    while(choice != 7){
        system("clear");
        std::cout << "1. PVA All Subjects \n";
        std::cout << "2. PVA One Subject \n";
        std::cout << "3. Average Peak Landing All Subjects \n";
        std::cout << "4. Average Peak Landing One Subject \n";
        std::cout << "5. Average Peak Take Off All Subjects \n";
        std::cout << "6. Average Peak Take Off One Subject \n";
        std::cout << "7. Previous Menu... \n";
        std::cin >> choice;
        switch(choice){
            case 1:
                for(int i=0; i<numSub; i++){
                    subjects[i]->createPVA_DAT();
                }
            case 7: break;
            default: std::cout << "Please enter a valid option \n";
        }
    }
}


void graphing(Subject **subjects, int numSub){
    int choice = 0;
    while(choice != 3){
        system("clear");
        std::cout << "1. Graph All Subjects \n";
        std::cout << "2. Graph One Subject \n";
        std::cout << "3. Previous Menu... \n";
        std::cin >> choice;
        switch(choice){
            case 1:
                for(int i=0; i<numSub; i++){
                    subjects[i]->graphAll();
                }
            case 3: break;
            default: std::cout << "Please enter a valid option \n";
        }
    }
}
