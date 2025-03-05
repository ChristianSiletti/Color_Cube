#include "list.h"

//************************************************************************

//Pre: None 
//Post: length & currPos have been initialized to zero.
ListClass::ListClass() //default construcutor
{
	currPos = 0;
	length = 0;

}//end default constructor

//************************************************************************

//Revised: Christian Siletti ~ 2/18/24 @ 05:58PM
//Pre: List exists 
//Post: currPos is set to next element in list 
void ListClass::NextPosition()
// sets currPos to next currPos in list
{
	// Check to see if the incrementation can be made
	if (currPos > length)	// Christian Siletti
		throw OutOfListBoundsException();

	currPos++;
}// end NextPosition

//************************************************************************

//Pre: List exists 
//Post: currPos has been set to the front of the List.
void ListClass::FirstPosition()
// sets currPos to beginning of list
{
	currPos = FIRST_POSITION;
}// end FirstPosition

//************************************************************************

//Pre: List exists 
//Post: currPos is set to last element in list 
void ListClass::LastPosition()
// sets currPos to last position of list
{
	currPos = length - 1;
}// end FirstPosition

//************************************************************************

//Pre : List exists 
//Post: if List has no elements true is returned, otherwise false.
bool ListClass::IsEmpty() const
// returns TRUE if list is empty
{
	return(length == EMPTY);
}//End IsEmpty

//************************************************************************

//Pre: List exists 
//Post: if List is full, true is returned, otherwise false. 
bool ListClass::IsFull() const
// returns TRUE if list is full
{
	return (length == MAX_ENTRIES);
}//End IsFull

//************************************************************************

//Pre: List exists. 
//Post: if currPos = length, true is returned, otherwise false 
bool ListClass::EndOfList() const
//returns true if currPos = EndOfList
{
	return (currPos >= length);
}//End EndOfList

//************************************************************************

//Pre: currPos contains valid position in list (Find has been called)
//Post: A copy of the pdm specified by PDM currPos has been returned
ItemRec ListClass::Retrieve() const
//returns elmnt specified by currPos
{
	if (!IsEmpty())
		return listArr[currPos];
	else
		throw EmptyListException();
}//End Retrieve

//************************************************************************

//Revised: Christian Siletti ~ 2/15/24 @ 10:35AM
//Revised: Christian Siletti ~ 2/18/24 @ 05:32PM
//Pre: target contains a keyType value to search List for. 
//Post: If target is found within the List, true is returned and 
//      currPos is set to the elements location in the list. If target is 
//      not found, false is returned.
bool ListClass::Find( /*in*/ KeyType target) //value to search for		
// sets PDM currPos to position of target..(or where it would be found)
{
	FirstPosition();

	if (IsEmpty())
		return false;
	else
	{   // search list  for target and set currPos if found
		// All x, y, z coordinates must be checked
		while ((listArr[currPos].key.x != target.x || // Christian Siletti
				listArr[currPos].key.y != target.y 
				|| listArr[currPos].key.z != target.z) && currPos < length)
		{
			currPos++;
		}
		// Decrement currPos if the item was not found, so that currPos does not go out of bounds
		if (currPos > length)	// Christian Siletti
			currPos--;

		return (listArr[currPos].key.x == target.x && listArr[currPos].key.y == target.y
			&& listArr[currPos].key.z == target.z);
	}
} //end Find

//************************************************************************

//Pre:	list contains space to insert item 
//Post: newItem has been inserted at the end of the list
void ListClass::Insert(/*in*/ ItemRec newItem)  //item to insert
//Inserts item at end of list
{
	if (!IsFull())
	{
		listArr[length] = newItem;
		length++;
	}
	else
		throw FullListException();

} //end Insert		 

//************************************************************************

//Revised: Christian Siletti ~ 2/18/24 @ 05:25PM
//Pre: currPos contains the location of the element to be deleted;
//     where (O <= position < length)(Find has been called)
//Post: element has been deleted from list. 
void ListClass::Delete()
// deletes record found at currPos
{
	if (!IsEmpty())
	{
		listArr[currPos] = listArr[length - 1];
		length--;

		// Check to see if the last item was deleted, to decrement currPos aswell
		if (currPos > length)	// Christian Siletti
			currPos--;
	}
	else
		throw EmptyListException();

}//end Delete

//************************************************************************

//Pre: List exists. 
//Post: List has been cleared.
void ListClass::Clear()
//clears list
{
	length = EMPTY;
	currPos = FIRST_POSITION;

} //end Clear

//************************************************************************

//Pre: List exists. 
//Post: Number of elements has been returned 
int ListClass::GetLength() const
//returns length to client
{
	return length;
} //end GetLength


//************************************************************************
//Pre: orig contains a list to be copied
//Post: applying list contains a copy of orig
void ListClass::operator = (const ListClass& orig)
//creates deep copy of orig
{
	for (int i = 0; i < orig.length; i++)
		listArr[i] = orig.listArr[i];
	currPos = orig.currPos;
	length = orig.length;

}//end operator =
