#ifndef LIST_H
#define LIST_H

//FileName : list.h 
//Author: Luke Musto 
//Revisionist: Christian Siletti
//Date: 2/15/24 
//Project List 
//
//Purpose: Contains the specification for an unordered list class.  The 
//	struct definition for the list should be placed in the file itemrec.h,
//  therefore no code change need be made within the implementation file 
//  to change the basic design of a list item. The maximum number of list 
//  entries it currently handles is 100. It provides the programmer with 
//	all methods necessary to implement a list. It contains 13 public and
//  10 protected methods. It also contains 4 private data elements.
//
//
//
//ASSUMPTIONS:  ******IMPORTANT!!!! READ THESE   ******
//(1): The definition of the struct ItemRec will be supplied by the client
//		in a file called ItemRec.h 
//(2): Struct ItemRec will contain as its first field a component named 
//		key which will be of KeyType. KeyType should be a typedef found in
//      ItemRec.h. The component field key will be used to search the list
//
// TO ENSURE PROPER CLASS FUNCTION:
//(3): On a DELETION, method Find() must be called before using Delete().
//	   to set currPos must be set to the item to be deleted. 
//
//
//EXCEPTION HANDLING/ERROR CHECKING:  
//(1) : EmptyListException() - thrown when an operation applied to an empty list
//							 methods  : Retrieve, Delete						
// 
//(2): Full ListException()- thrown when Insert is attempted on a full list  
//
//(3): OutOfListBoundsException() - thrown when the current position is attempted to be 
//									incremented out of the bounds of the current list length
//REVISIONS:
//Christian Siletti:
//		1 - Updated Find Method to work with the LocationRec
//		2 - Updated Delete to decrement currPos on deletion of final list element
//		3 - Updated Find to decrement currPos when the item is not found
//	   
//
//                       SUMMARY OF METHODS: 
//
//PUBLIC METHODS
//
//ListClass();           set private data members length & currPos to zero
//						
//void  FirstPosition(); sets currPos  to beginning of list 
//void  NextPosition();  sets currPos  to next element in list 
//void  LastPosition();  sets currPos  to last element in the list
// 
//bool  IsEmpty();       returns true  if  List has no elements.
//bool  IsFull();        returns true  if List is full, false otherwise 
//bool  EndofList();     returns true  if currPos specifies end of List
//						   (1st empty position in the List). 
//ItemRec Retrieve();   returns a record (ItemType) specified by currPos 
//
//bool Find(/*in*/ KeyType target);	finds position of target within list 
//									returns true if found, false otherwise
// 
//void Insert(/*in*/ ItemType newItem); 
//   --inserts target into list at position end of the list 
//   --List can not be full 
//
//void Delete(); Deletes ListEntry specified by currPos 
//	 -- NOTE: Find must be called before deleting a list entry	
//
//void Clear();   Clears list and sets length and currPos to zero.
//
//int GetLength();  returns ths number of items in the list. 
//
//void operator = (const ListClass& orig); creates a deep copy of orig
// 
//PRIVATE MEMBERS: 
//int length;                            //length of list 
//int currPos;                           //current position in the List
//
//ItemRec listArr[MAX_ENTRIES]			 // List


#include "itemrec.h"  // SUPPLIED BY CLIENT FOR DEFINITION OF CLASS
					  // CONTAINS LAYOUT OF ELEMENT TO BE STORED IN LIST

#include "ListExceptions.h" // For List Exception Classes

//Constant Declarations 
const int MAX_ENTRIES = 125;						//max elements in list
const int FIRST_POSITION = 0;						//list minimum 
const int EMPTY = 0;								//list empty 


// Class Declarations 
class ListClass
{
public:
	ListClass(); //default constructor; 
	//sets private data members length & currPos to zero
	//Pre: None 
	//Post: length & currPos have been initialized to zero.

	void FirstPosition();
	//sets currPos to begining of list 
	//Pre: List exists 
	//Post: currPos has been set to the front of the List.

	void NextPosition();
	//sets currPos to next element in list
	//Pre: List exists 
	//Post: currPos is set to next element in list 
	//Exceptions Thrown: EmptyListException()- thrown when NextPosition 
	//		attempted on last list item		

	void LastPosition();
	//sets currPos to last element in list
	//Pre: List exists 
	//Post: currPos is set to last element in list 

	bool IsEmpty() const;
	//returns true if List has no elements. 
	//Pre : List exists 
	//Post: if List has no elements true is returned, otherwise false 

	bool IsFull() const;
	//returns true if List is full(length = MAX_ENTRIES)
	//Pre: List exists 
	//Post: if List is full, true is returned, otherwise false. 

	bool EndOfList() const;
	//returns true if currPos specifies end of List. 
	//Pre: List exists. 
	//Post: if currPos = length, true is returned, otherwise false 

	ItemRec Retrieve() const;
	//returns a record of type ItemType specified by currPos. 
	//Pre: currPos contains valid position in list
	//     (Find has been called)
	//Post: A copy of the pdm record specified by PDM currPos 
	//		has been returned
	//Exceptions Thrown: EmptyListException()- thrown when retrieve 
	//		attempted on empty list					 

	bool Find(/* in */KeyType target);		//Item to search for
	//finds position of key within the OrdList. 
	//Pre: target contains a keyType value to search List for. 
	//Post: If target is found within the List, true is returned and 
	//		currPos is set to the elements location in the list. If 
	//		target is not found, false is returned.

	void Insert(/* in */ ItemRec newItem); // Item to insert
	//inserts newItem into list at end  
	//Pre:	list contains space to insert item 
	//Post: newItem has been inserted at the end of the list
	//Exceptions Thrown: FullListException()- thrown when insert 
	//		attempted on full list		

	void Delete();
	//deletes list entry specified by currPos, 
	//Pre: currPos contains the location of the element to be deleted
	//     where (O <= position < length)(Find has been called)
	//Post: element has been deleted from list. 
	//Exceptions Thrown: EmptyListException()- thrown when delete 
	//		attempted on empty list		

	void Clear();
	//clears the List 
	//Pre: List exists. 
	//Post: List has been cleared.

	int GetLength() const;
	//returns the number of entries in the the List 
	//Pre: List exists. 
	//Post: Number of elements has been returned 

	//overloaded operators
	void operator = (const ListClass& orig);
	//creates a deep copy of the list
	//Pre: orig contains a list to be copied
	//Post: applying list contains a copy of orig


private:
	int length;						//length (occupied elements) of list 
	int currPos;					//specifies current position in list 

	ItemRec listArr[MAX_ROW * MAX_COL * MAX_DEP];	  // List
	// Set to largest possible contiguous color - Christian Siletti

};//end ListClass 

#endif