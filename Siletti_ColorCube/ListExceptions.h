#ifndef EXCEPTION_H
#define EXCEPTION_H

//FileName : ListExceptions.h 
//Author:	Luke Musto 
//Date: 2/12/23 
//
//Purpose: This file contains the definition of the exception classes thrown within the 
//		   the  listclass. 


// An EmptyListException is thrown when a Retrieve or Delete is attempted on an empty list
class EmptyListException
{};


// A FullListException is thrown when an Insert is attempted on an full list
class FullListException
{};

// A OutOfListBoundsException - thrown when the current position is attempted to be incremented out
//								of the bounds of the current list length
class OutOfListBoundsException
{};

#endif