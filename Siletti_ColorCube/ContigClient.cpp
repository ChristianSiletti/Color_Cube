/*
	FileName : ContigClient.cpp
	Author: Christian Siletti
	Date: 2/18/24
	Project Color Cuberator

	PURPOSE:
		To find the largest and second largest contiguous block of colors in a 
		3 dimensional cube, and to display it to an output file, along with other cube statistics.

	INPUT:
		NO INPUT FROM USER ALL NEEDED DATA WITHIN Constants.h

	PROCESSING:
		A color cube is populated with random colors
		Those colors are kept track of in the colorArray
		The largest contiguous color and second largest contiguous color are found
		The most populous color and second most populous color are found

	OUTPUT:
		All outputs go to OUTPUT_FILE_NAME
		Outputs the largest contiguous block of cells within the cube,
		and the second largest if it is of same length.
		The amount of cells within these contiguous blocks are printed.
		A Color summary is printed containing the amount of each color,
		and the two most populous colors, along with the percent of the cube they take up

	ASSUMPTIONS:  ******IMPORTANT!!!! READ THESE   ******
		1 - For added colors, their cases must be added in the ColorEnumIndexToString function
		2 - The color array will be initialized before the cube is populated
		3 - If a third contiguous block is found to be the same size as the second largest contiguous
			block, just ignore it, first found stays


	EXCEPTION HANDLING/ERROR CHECKING:
		1 - If an invalid location is sent into the CubeClass the program will move on
		2 - If the cube is too small (1x1x1) the contiguous block will not be outputted, there
			is no point.

						   SUMMARY OF FUNCTIONS:
PopulateCube(*OUT*CubeClass& colCube,
			 *IN/OUT*ColorArr colArr)
		- To populate the color cube with random colors and to collect data on the amount of each color
InitializeColorArray(*OUT*ColorArr colArr)
		- To set all indexes in a ColorArr to 0
PrintContig(*IN* ListClass& colLocList,
			*IN* const ColorEnum& cellCol,
			*IN/OUT*ofstream& dout)
		- To print the cube highlighting a series of cells whose colors are contiguous
Move(*IN*const DirectionEnum& dir,
	 *IN/OUT*LocationRec& currPos) 
		- Increment a LocationRec in a single direction
ColorStats(*IN*const ColorArr colArr,
		   *IN/OUT*ofstream& dout)
		- Output color statistics to an output file
CoveragePercentage(*IN*const int& colAmt)
		- To determine and return the percentage that a color takes up of the cube
FindPopulousColors(*IN*const ColorArr colArr,
				   *OUT*int& popIndex,
				   *OUT*int& secPopIndex)
		- Determine the two most populous colors
ColorEnumIndexToString(*IN*const int& index)
		- To convert the integer index of a ColorEnum to a string
*/
#include<fstream>	// Used to create output files
#include<iomanip>	// Used for output manipulation
#include "Cube.h"	// Grants Access to Cube Class
#include "list.h"	// Grants Access to List Class
#include <iostream>	// For Testing Purposes
using namespace std;	// Standard namespace



// Constants
typedef int ColorArr[MAX_COLOR_AMT][COLOR_TRACKER];	// Array used to store color amount information



// Prototypes
void PopulateCube(/*OUT*/CubeClass&,			 // The cube being populated
				  /*IN/OUT*/ColorArr);			 // A tracker to store the amount of each color
void InitializeColorArray(/*OUT*/ColorArr);		 // The color array being initialized
void Move(/*IN*/const DirectionEnum&,			 // The desired direction to move in
		  /*IN/OUT*/LocationRec&);				 // The current location
void PrintContig(/*IN*/ ListClass&,				 // A list of the locations of the cells to be printed
				 /*IN*/ const ColorEnum&,		 // The cells colors
				 /*IN/OUT*/ofstream&);			 // The output file
void ColorStats(/*IN*/const ColorArr,			 // The color array whose stats are being printed
				/*IN/OUT*/ofstream&);			 // The output file
float CoveragePercentage(/*IN*/const int&);		 // The amount of the color in the cube
void FindPopulousColors(/*IN*/const ColorArr,	 // The color array whose being analyzed
						/*OUT*/int&,			 // Holds the most populous color's index	
						/*OUT*/int&);			 // Holds the second most populous color's index
string ColorEnumIndexToString(/*IN*/const int&); // The integer index of a ColorEnum




int main()
{
	ListClass largContigList = ListClass();		// Holds all positions of the largest 
												// contiguous block of colors
	ListClass secLargContigList = ListClass();	// Holds all positions of the second largest 
												// contiguous block of colors
	ListClass currList = ListClass();		// The current contiguous block being checked
	CubeClass colorCube = CubeClass();		// Simulates and holds data on ColorCube
	ColorArr colorArr;					// Keeps track of the amount of colors, and the amount checked
	ofstream dout;						// The output file everything will be outputted to
	srand(SEED);						// The random number generator with its specified seed
	ItemRec currItem;					// The current item / position being viewed
	ColorEnum currCol;					// The current color being viewed
	bool done = false;					// A bool that controls when the cube is done being searched


	// Set all elements in the color array to zero
	InitializeColorArray(colorArr);

	// Populate the cube with random colors, and keep track of the color counts
	PopulateCube(colorCube, colorArr);


	// ---------------- Find Largest and Second Largest Contiguous Blocks -----------------

	
	// Set the initial position to zero
	currItem.key.x = 0;
	currItem.key.y = 0;
	currItem.key.z = 0;
	

	// Repeats until done is marked as true aka the whole cube is checked
	while (!done)
	{
		// Check if the last cell is being looked at
		if (currItem.key.x == MAX_ROW - OFFSET 
			&& currItem.key.y == MAX_COL - OFFSET 
			&& currItem.key.z == MAX_DEP - OFFSET)
			done = true;	// The search for largest contig is over

		else
		{
			// Get the color of the cell
			currCol = colorCube.GetType(currItem.key);

			// Check if the status of the cell is not checked
			if (!colorCube.GetStatus(currItem.key))
			{
				// The cell hasn't been checked yet!
				 
				// Check if the color has no chance at being one of the 
				// top two largest contiguous colors
				if (colorArr[(int)currCol][ZERO] - colorArr[(int)currCol][OFFSET] <= 
					secLargContigList.GetLength())
				{
					// This cell has no chance, set it to checked and move on
					colorCube.SetStatus(currItem.key, CHECKED);
				}
				else
				{
					// Reset the current list
					currList.Clear();

					// Insert the first spot in the list
					currList.Insert(currItem);

					// Set the status of the cell to checked
					colorCube.SetStatus(currItem.key, CHECKED);
					
					// Increment the amount of colors checked in the color array
					colorArr[(int)currCol][OFFSET]++;

					do
					{
						// Chech each adjacent cell to see if it is the same color
						// and that it has not yet been checked
						for (int i = 0; i <= MAX_NUM_DIR; i++)
						{
							// Update the location
							Move((DirectionEnum)i, currItem.key);

							try
							{
								// Check if the cell is the same color and hasn't yet been checked
								if (colorCube.GetType(currItem.key) == currCol && 
									colorCube.GetStatus(currItem.key) != CHECKED)
								{
									// Insert the location if it is contiguous with the starting block
									currList.Insert(currItem);

									// Set the cell to checked
									colorCube.SetStatus(currItem.key, CHECKED);

									// Increment the amount of colors checked in the color array
									colorArr[(int)currCol][OFFSET]++;
								}
							}
							catch (OutOfBoundsException)
							{
								// Do nothing just move on
							}

							// Move the location back to the starting location
							if (i % 2 == ZERO)	// If the index is even offset by positive one
								Move((DirectionEnum)(i + OFFSET), currItem.key);

							else				// Else offset by negative one
								Move((DirectionEnum)(i - OFFSET), currItem.key);

						}// end for

						// Go to the oldest cell addition and check repeat the contiguous check on it
						currList.NextPosition();

						// Update the location to the new position to be checked
						currItem = currList.Retrieve();

						// Repeat until all of currlist has been checked
					} while (currList.EndOfList() == false);
					
					// Check to see if the current list is will become either the 
					// largest contiguous block of colors or the second largest
					if (currList.GetLength() > largContigList.GetLength())	// Current is the largest
					{
						// Largest becomes the second largest
						secLargContigList = largContigList;

						// Current list becomes the largest
						largContigList = currList;
					}
					// Current is the second largest
					else if (currList.GetLength() > secLargContigList.GetLength())	
					{
						// Current list becomes the second largest
						secLargContigList = currList;
					}

				}// end else

				// Go back to the original cell
				currList.FirstPosition();

				// Reset the location back to the original location
				currItem = currList.Retrieve();

			}// end if

			
			// Increment to the next cell column wise
			currItem.key.y++;

			// Check if the position should be moved to the next depth
			if (currItem.key.y >= MAX_COL)
			{
				// Increment depth
				currItem.key.z++;
				// Reset Column
				currItem.key.y = 0;
			}
			// Check if the position should be moved to the next row
			if(currItem.key.z >= MAX_DEP)
			{
				// Increment row
				currItem.key.x++;
				// Reset depth
				currItem.key.z = 0;
			}

		}// end else

	}// end while


	// ---------------- The Search Ends -----------------


	// Open the output file
	dout.open(OUTPUT_FILE_NAME);


	// Reset the contiguous lists to the beginning
	largContigList.FirstPosition();
	secLargContigList.FirstPosition();


	// The try is here incase the cube is too small (1x1x1)
	try
	{
		// Get the largest contiguous color
		currCol = colorCube.GetType(largContigList.Retrieve().key);

		// Title the largest contiguous block
		dout << "Largest Contiguous Block:" << endl;

		// Print the largest contiguous block
		PrintContig(largContigList, currCol, dout);

		// Output the amount of cells contained within this block
		dout << "\n[There are " << largContigList.GetLength() << " "
			 << ColorEnumIndexToString((int)currCol)
			 << " cells within this block]\n";


		// Get the second largest contiguous color
		currCol = colorCube.GetType(secLargContigList.Retrieve().key);

		// Check to see if the second largest contiguous list is the same size as the largest
		if (secLargContigList.GetLength() == largContigList.GetLength())
		{

			// Title the second largest contiguous block
			dout << "\nSecond Largest Contiguous Block:" << endl;

			// Print the second largest contiguous block
			PrintContig(secLargContigList, currCol, dout);

			// Output the amount of cells contained within this block
			dout << "\n[There are " << secLargContigList.GetLength() << " " 
				<< ColorEnumIndexToString((int)currCol)
				<< " cells within this block]\n";
		}// end if
		// Else just print statistics for second largest contiguous block
		else
		{
			// Output the amount of cells contained within the second largest block
			dout << "\n[There are " << secLargContigList.GetLength() << " " 
				<< ColorEnumIndexToString((int)currCol)
				<< " cells within the second largest contiguous block]\n";
		}

	}// end try
	catch (EmptyListException)
	{
		// Output a message stating the cause of the lack of output
		dout << "Cube too small to print!\n";
	}


	// Output the color statistics to the output file 
	ColorStats(colorArr, dout);

	// Close the output file
	dout.close();

}// end main





// --------------------------------- FUNCTIONS ------------------------------------------


//O(N^3)
//Purpose: To populate the color cube with random colors and to collect data on the amount of each color
//Pre: The cube to be populated, and an array to store the colors information
//	   The color array should be set to its default values ie... InitializeColorArray
//Post: The cube will be populated with random colors, and the color amounts will be known
void PopulateCube(/*OUT*/CubeClass& colCube,	// The cube being populated
				  /*IN/OUT*/ColorArr colArr)		// A tracker to store the amount of each color
{
	ColorEnum currColor;		// The current color being stored into the cube
	LocationRec currLoc;	// The current cell being populated

	// Cycle through each cell and populate it with a random color
	for (int i = 0; i < MAX_ROW; i++)
	{
		currLoc.x = i;	// Update the row
		for (int j = 0; j < MAX_COL; j++)
		{
			currLoc.y = j;	// Update the column
			for (int k = 0; k < MAX_DEP; k++)
			{
				currLoc.z = k;	// Update the depth

				currColor = (ColorEnum)(rand() % MAX_COLOR_AMT); // Get a random color

				colCube.SetType(currLoc,currColor);	// Populate the cell with the color

				// Increment the color count
				colArr[(int)currColor][ZERO]++;
			}// k
		}// j
	}// i
}// end PopulateCube


// --------------------------------------------------------------------------------------


//O(N^2)
//Purpose: To set all indexes in a ColorArr to 0
//Pre: The ColorArr being initialized
//Post: All indexes in ColorArr are 0
void InitializeColorArray(/*OUT*/ColorArr colArr)	// The color array being initialized
{
	// Cycle through the array
	for (int i = 0; i < MAX_COLOR_AMT; i++)
		for (int j = 0; j < COLOR_TRACKER; j++)
			colArr[i][j] = ZERO;	// Set the index to zero
}// end InitializeColorArray


// --------------------------------------------------------------------------------------


// O(1)
// Purpose: Increment a LocationRec in a single direction
// Pre: The desired location and the LocationRec being changed
// Post: The LocationRec will be updated to the new location
void Move(/*IN*/const DirectionEnum& dir,	// The desired direction to move in
		  /*IN/OUT*/LocationRec& currPos)	// The current location
{
	// Increment currPos according to the specified direction
	switch (dir)
	{
	case UP:
			currPos.y++;
		break;
	case DOWN:
			currPos.y--;
		break;
	case NORTH:
			currPos.z++;
		break;
	case SOUTH:
			currPos.z--;
		break;
	case EAST:
			currPos.x++;
		break;
	case WEST:
			currPos.x--;
		break;
	default:
		break;
	};

}// end Move


// --------------------------------------------------------------------------------------


// O(N^2)
// Purpose: To print the cube highlighting a series of cells whose colors are contiguous
// Pre: The list of contiguous cells, their color, and the output file to output to
// Post: The cube will be outputted layer by layer with the indicated cells specifying their color,
//		 all other cells will be marked with "***" as null status
void PrintContig(/*IN*/ ListClass& colLocList,	 // A list of the locations of the cells to be printed
				/*IN*/ const ColorEnum& cellCol, // The cells colors
				/*IN/OUT*/ofstream& dout)		 // The output file
{
	LocationRec tempLoc;	// The location being analyzed

	// Cycle through the rows
	for (int i = 0; i < MAX_ROW; i++)
	{
		tempLoc.x = i;	// Update tempLoc

		// Cycle through the faces 
		for (int k = MAX_DEP - 1; k >= 0; k--)
		{
			dout << endl;	// Go to next line
			tempLoc.z = k;	// Update tempLoc

			// Cycle through the columns
			for (int j = 0; j < MAX_COL; j++)
			{
				tempLoc.y = j;	// Update tempLoc

				// See if the location is in the list
				if (colLocList.Find(tempLoc))
				{
					// Output the color of the cell if it is
					dout << ColorEnumIndexToString((int)cellCol) << "\t";
				}
				else // Otherwise print null status
					dout << "***" << "\t";
			}// end j
		}// end k
		dout << endl;	// Go to next line
	}// end i

}// end PrintContig


// --------------------------------------------------------------------------------------


//O(N)
//Purpose: Output color statistics to an output file
//Pre: Output file must be open, the color Array being printed
//Post: The color statistics will be outputted to the output file
void ColorStats(/*IN*/const ColorArr colArr,		// The color array whose stats are being printed
				/*IN/OUT*/ofstream& dout)			// The output file
{
	int popIndex;		// Holds the most populous color's index
	int secPopIndex;	// Holds the second most populous color's index

	// Find the most populous colors
	FindPopulousColors(colArr, popIndex, secPopIndex);

	// Output title
	dout << endl << "Color Statistics:\n";

	// Output the amount of each color
	for (int i = 0; i < MAX_COLOR_AMT; i++)
		dout << ColorEnumIndexToString(i) << " Cells: " << colArr[i][ZERO] << "\n";

	// Get the percentages to output to the correct decimal place
	dout << fixed << showpoint << setprecision(2);

	// Output the principle color and its coverage percentage
	dout << "The principle color was " << ColorEnumIndexToString(popIndex)
		<< ", it took up " << CoveragePercentage(colArr[popIndex][ZERO]) << "% of the cube.\n";

	// Output the second most populous color and its coverage percentage
	dout << "The second most populous color was " << ColorEnumIndexToString(secPopIndex)
		<< ", it took up " << CoveragePercentage(colArr[secPopIndex][ZERO]) << "% of the cube.";


}// end ColorStats


// --------------------------------------------------------------------------------------


//O(1)
//Purpose: To determine and return the percentage that a color takes up of the cube
//Pre: The amount of cells with the color in the cube
//Post: The percent that the color takes up within the cube
float CoveragePercentage(/*IN*/const int& colAmt)	// The amount of the color in the cube
{
	return	(float)colAmt / (float)(MAX_ROW * MAX_COL * MAX_DEP) * (float)PERCENT_CONVERTER;
}// end CoveragePercentage

// --------------------------------------------------------------------------------------


// O(N)
// Purpose: Determine the two most populous colors
// Pre: The array of colors should be filled, places to store the populous color's indexes
// Post: The populous color indexes will be returned
void FindPopulousColors(/*IN*/const ColorArr colArr,	// The color array whose being analyzed
	/*OUT*/int& popIndex,			// Holds the most populous color's index	
	/*OUT*/int& secPopIndex)		// Holds the second most populous color's index
{
	// Get an initial value for popIndex
	popIndex = ZERO;

	// Check the first two colors against each other to determine their popularity order
	if (colArr[popIndex][ZERO] < colArr[OFFSET][ZERO])
	{
		secPopIndex = popIndex;
		popIndex = OFFSET;		// Get an initial value for secPopIndex
	}

	else
		secPopIndex = OFFSET;		// Get an initial value for secPopIndex

	// Iterate through all the colors and determine the two most populous colors
	for (int i = 2; i < MAX_COLOR_AMT; i++)
	{
		// Check if the color amount is greater than the second largest
		if (colArr[i][ZERO] > colArr[secPopIndex][ZERO])
		{
			// Check if the color amount is greater than the largest
			if (colArr[i][ZERO] > colArr[popIndex][ZERO])
			{
				// Update the color popularity order
				secPopIndex = popIndex;
				popIndex = i;
			}
			else
				// Update the color popularity order
				secPopIndex = i;
		}
	}
}// end FindPopulousColors


// --------------------------------------------------------------------------------------

//O(1)
//Purpose: To convert the integer index of a ColorEnum to a string
//Pre: The integer index
//Post: The corresponding color will be returned
string ColorEnumIndexToString(/*IN*/const int& index)	// The integer index of a ColorEnum
{
	// Determine the color based off the index
	switch (index)
	{
	case 0: return "RED";		break;
	case 1: return "ORG";		break;
	case 2: return "YEL";		break;
	case 3: return "GRN";		break;
	case 4: return "BLU";		break;
		// *ADDITIONAL COLOR CASES GO HERE* 
	default: return "OTH";	// Short for other color

	};
}// end ColorEnumIndexToString


// Use this code under populate cube to print out the cube by cell color
// - Maybe it'll make grading easier!
/*
	LocationRec tempLoc;

	for (int i = 0; i < MAX_ROW; i++)
	{
		cout << endl;
		tempLoc.x = i;
		for (int k = MAX_DEP - 1; k >= 0; k--)
		{
			tempLoc.z = k;
			cout << endl;
			for (int j = 0; j < MAX_COL; j++)
			{
				tempLoc.y = j;
				cout << ColorEnumIndexToString((int)colorCube.GetType(tempLoc)) << " ";
			}
		}
	}
*/


/* --------------------------------------- Appended OutPut -------------------------------------------
										   (AKA Appendage)
	Largest Contiguous Block:

	***	***	***	
	ORG	***	***	
	***	***	***	

	ORG	ORG	***	
	ORG	***	***	
	ORG	***	***	

	***	ORG	***	
	ORG	***	***	
	***	***	***	

	[There are 7 ORG cells within this block]

	[There are 2 GRN cells within the second largest contiguous block]

	Color Statistics:
	RED Cells: 5
	ORG Cells: 8
	YEL Cells: 4
	GRN Cells: 5
	BLU Cells: 5
	The principle color was ORG, it took up 29.63% of the cube.
	The second most populous color was RED, it took up 18.52% of the cube.


   ------------------------------------------------------------------------------------------------ */
