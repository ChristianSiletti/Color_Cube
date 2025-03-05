#pragma once
/*
    FileName : Constants.h
    Author: Christian Siletti
    Date: 2/13/24
    Project Color Cuberator

    Purpose: This file contains the constants and enums used in color cuberator

    Assumptions:
        The MAX ROW, COL, and DEP should be greater than 0 each
*/

#include <string>   // Gives access to string datatype
using namespace std;


// Enumerated type to keep track of cell color
enum ColorEnum { RED, ORG, YEL, GRN, BLU };
const int MAX_COLOR_AMT = 5;	// The maximum number of colors
// A case must be added to the ColorEnumIndexToString function in ContigClient


// Enumerated type to determine direction of travel
enum DirectionEnum { NORTH, SOUTH, EAST, WEST, UP, DOWN };
const int MAX_NUM_DIR = 6;  // The number of directions to move in


// Struct to contain an x y z position
struct LocationRec
{
    int x;     // The row position
    int y;     // The column position
    int z;     // The depth position
};


// Constants
const int MAX_ROW = 5;              // Maximum amount of rows
const int MAX_COL = 5;              // Maximum amount of columns
const int MAX_DEP = 5;              // Maximum amount of faces
const int COLOR_TRACKER = 2;	    // The number of specific details needed to track for each color
const int ZERO = 0;                 // A lower index bound
const int OFFSET = 1;               // Amount to offset a number by one
const int SEED = 1234567;           // The random seed used
const int PERCENT_CONVERTER = 100;  // The number used to convert a number to a percentage

const bool CHECKED = true;          // Used to set cells to being checked

const string OUTPUT_FILE_NAME = "Cube.out";	// The output file name
