#pragma once
/*
	FileName : Exceptions.h
	Author: Christian Siletti
	Date: 2/14/24
	Project Color Cuberator

	Purpose: This file contains the exceptions for the cube class

*/

// Exception for when currPos is attempted to be moved outside the cube
class OutOfBoundsException
{};

// Exception for getting the type of cell, when the cell has no type
class EmptyTypeException
{};