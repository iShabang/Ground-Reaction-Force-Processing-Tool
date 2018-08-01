
#include <iostream>
#include <fstream>
#include "subClass.h"
#include <stdlib.h>

void inputData(Subject **, int);
void calculations(Subject **, int);
void graphing(Subject **, int);
void settings();
void changeInfo();

int main()
{
    std::ofstream output;
    std::ifstream input;
/*******************************************************************
 * This section will ask for necessary variables to create an object
   on first run. Information is saved and used on future runs.
*******************************************************************/

    Subject **subjects; 
    int choice = 1, numSub, numCond, numTrials;

    input.open("info.txt");
    if(!input){
        system("clear");
        std::cout << "Enter number of subjects: "; std::cin >> numSub;
        std::cout << "Enter number of conditions: "; std::cin >> numCond;
        std::cout << "Enter number of trials: "; std::cin >> numTrials;
        output.open("info.txt");
        output << numSub << ' ' << numCond << ' ' << numTrials << '\n';
        output.close();
    }
    else{
        input >> numSub >> numCond >> numTrials;
        input.close();
    }

/*******************************************************************
 * Create objects with user specified parameters
*******************************************************************/
    subjects = new Subject*[numSub];
    for(int i=0; i<numSub; i++){
        subjects[i] = new Subject(i+1, numCond, numTrials);
    }

/*******************************************************************
 * Main Menu
*******************************************************************/
    while(choice != 5){
        system("clear");
        std::cout << "1. Input Data \n";
        std::cout << "2. Calculations \n";
        std::cout << "3. Graphing \n";
        std::cout << "4. Settings \n";
        std::cout << "5. Exit \n";


        std::cin >> choice;
        switch (choice){
            case 1: inputData(subjects, numSub);
                    break;
            case 2: calculations(subjects, numSub);
                    break;
            case 3: graphing(subjects, numSub);
                    break;
            case 4: settings(); 
                    break;

            case 5: break;
        }
        
        
    }

    system("clear");
    return 0;
}

/****************************************************************************
Function Name:      inputData
Parameters:         pointer to array of subjects, number of subjects
Return Value:       void
Purpose:            Menu for data input. User can input all or one subject
                    Creates a directory for user to input data into. 
****************************************************************************/
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
    int sub;
    while(choice != 3){
        system("clear");
        std::cout << "1. Input All Subjects \n";
        std::cout << "2. Input One Subject \n";
        std::cout << "3. Previous Menu... \n";
        std::cin >> choice;
        switch(choice){
            case 1:
                for(int i=0; i<numSub; i++){
                    subjects[i]->createDATfiles();
                }
                break;

            case 2:
                std::cout << "Enter subject number: "; std::cin >> sub;
                subjects[sub-1]->createDATfiles();
                break;

            case 3: break;
            default: std::cout << "Please enter a valid option \n";
        }
    }
}

/****************************************************************************
Function Name:      calculations
Parameters:         pointer to array of subjects, number of subjects
Return Value:       void
Purpose:            Menu for calculations. Each option is linked to a 
                    different set of calculations. Peak values are determined
                    during PVA calculations
****************************************************************************/

void calculations(Subject **subjects, int numSub){
    std::ofstream output;
    int choice = 0, sub;
    while(choice != 6){
        system("clear");
        std::cout << "1. PVA All Subjects \n";
        std::cout << "2. PVA One Subject \n";
        std::cout << "3. Average Peak Landing All Subjects \n";
        std::cout << "4. Average Peak Take Off All Subjects \n";
        std::cout << "5. Average Peak Velocity All Subjects \n";
        std::cout << "6. Previous Menu... \n";
        std::cin >> choice;
        switch(choice){

            case 1:
                for(int i=0; i<numSub; i++){
                    subjects[i]->createPVA_DAT();
                }
                break;

            case 2:
                std::cout << "Enter subject number: "; std::cin >> sub;
                subjects[sub-1]->createPVA_DAT();
                break;

            case 3:
                for(int i=0; i<numSub; i++){
                    subjects[i]->avgPeak(output);
                    
                }
                break;

            case 4:
                for(int i=0; i<numSub; i++){
                subjects[i]->avgPeakTakeoff(output);
                }
                break;

            case 5:
                for(int i=0; i<numSub; i++){
                    subjects[i]->avgPeakVelocity(output);
                }
                break;

            case 6: break;
            default: std::cout << "Please enter a valid option \n";
        }
    output.close();
    }
}

/****************************************************************************
Function Name:      graphing
Parameters:         pointer to array of subjects, number of subjects
Return Value:       void
Purpose:            Menu for graphing data. Only supports graphing all data
                    at once for one subject and all subjects
****************************************************************************/


void graphing(Subject **subjects, int numSub){
    int choice = 0, sub;
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
                break;
            case 2:
                std::cout << "Enter subject number: "; std::cin >> sub;
                subjects[sub-1]->graphAll();
                break;
            case 3: break;
            default: std::cout << "Please enter a valid option \n";
        }
    }
}

/****************************************************************************
Function Name:      settings
Parameters:         NONE
Return Value:       void
Purpose:            Menu for changing base information
****************************************************************************/

void settings(){
    int choice = 0;
    while(choice != 2){
        system("clear");
        std::cout << "1. # of Subjects, Conditions, Trials \n";
        std::cout << "2. Previous menu... \n";
        std::cin >> choice;
        switch(choice){
            case 1: changeInfo(); 
                    break;
            case 2: break;
            default: std::cout << "Invalid option \n";
        }
    }
}


/****************************************************************************
Function Name:      changeInfo
Parameters:         NONE
Return Value:       void
Purpose:            requests new # of subjects, conditions, and trials from 
                    the user and overwrites info.txt
****************************************************************************/

void changeInfo(){
    std::ofstream output;
    int numSub, numCond, numTrials;
    system("clear");
    std::cout << "Enter number of subjects: "; std::cin >> numSub;
    std::cout << "Enter number of conditions: "; std::cin >> numCond;
    std::cout << "Enter number of trials: "; std::cin >> numTrials;
    output.open("info.txt");
    output << numSub << ' ' << numCond << ' ' << numTrials << '\n';
    output.close();
    return;
}
