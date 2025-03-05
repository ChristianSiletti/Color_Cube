#ifndef ITEMREC_H
#define ITEMREC_H


/*
	FileName : itemrec.h
	Author: Christian Siletti
	Date 2/15/24
	Project Color Cuberator

	Purpose: This file contains the specification for an item to be stored
			   in a list class.

	ASSUMPTIONS:
	(1) : Struct ItemRec will contain as its first field a component named
		  key which will be of KeyType. KeyType as defined below is the
		  component field key used to search the list.
*/
#include "Constants.h"	// Gives access to LocationRec

typedef LocationRec KeyType;		// Datatype used for key

// Struct to be stored within the list
struct ItemRec
{
	KeyType key;	// key used to search/compare elements of list
};

#endif