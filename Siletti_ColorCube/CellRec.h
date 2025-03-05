#pragma once
/*
	FileName : Cellrec.h
	Author: Christian Siletti
	Date: 2/13/24
	Project Color Cuberator

	Purpose: This file contains the specification for an item to be stored
			 in a cube class.

	ASSUMPTIONS:
		1 - Struct CubeRec will contain as its first field a component named
			type which will be of CellType. CellType as defined below is the
			component field type used to check what type of cell the cell in the
			cube is.
		2 - Struct CubeRec will contain as its second field a component named
			status which will be a bool. Bool status is to check on the state
			of the cell, details for what that implies should be commented.
		3 - Struct CubeRec will contain as its third field a component named
			populated which will be a bool. Bool populated is to check on if
			the cell has been given a specific type yet.
		4 - Must contain a 3 dimensional array of typedef CellRec, named Cube3DArr
*/

#include "Constants.h"	// File which contains constant values used


typedef ColorEnum CellType;	// Datatype stored in a cube class's cell

// struct to be stored in the cube
struct CellRec
{

	CellType type;	// The type of cell that particular cell is

	bool status;	// Boolean for whether the cell has been deemed as checked or not
	// True ~ Checked	/	False ~ Not Checked

	bool populated;	// Boolean for whether the cell has been given a type or not
};


typedef CellRec Cube3DArr[MAX_ROW][MAX_COL][MAX_DEP];	// The 3D cube itself