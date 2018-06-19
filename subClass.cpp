#include "subClass.h"

/*****************************************************************************************
 * Function Name:   Subject - Default Constructor
 * Parameters:      NONE
 * Return Type:     NONE
 * Purpose:         Initializes all private members to their default 
*****************************************************************************************/
Subject::Subject()
{
    name = "";
    motion = "";
    trials = 0;
}

/*****************************************************************************************
 * Function Name:   Subject - constructor with parameters
 * Parameters:      NONE
 * Return Type:     NONE
 * Purpose:         Initializes object with private members assigned to values given in
 *                  parameters.
*****************************************************************************************/
Subject::Subject(string n, string m, int t)
{
    name = n;
    motion = m;
    trials = t;
}

/*****************************************************************************************
 * Function Name:   readInData()
 * Parameters:      NONE
 * Return Type:     Void
 * Purpose:         Reads in data using function defined in readFunc header
*****************************************************************************************/
void Subject::Subject()
{
    readVector();
}
