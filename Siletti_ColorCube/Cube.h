#pragma once
/*
    FileName : Cube.h
    Author: Christian Siletti
    Date: 2/14/24
    Project Color Cuberator

    PURPOSE:
        Contains the specifications for a Cube Class. The struct definition for the
        cube's cells should be placed in the file CellRec.h.


    ASSUMPTIONS:  ******IMPORTANT!!!! READ THESE   ******
        1 - The definition of the struct CellRec will be supplied by the client
            in a file called CellRec.h
        2 - Struct CellRec will contain type as its first field a component named
            type which will be of CellType. CellType should be a typedef found in
            CellRec.h. The component field type will be used to set the type of
            each cell
        3 - Struct CellRec will contain as its second field a bool named
            status. The component field status will be used to set the status of
            the cell
        4 - Struct CubeRec will contain as its third field a component named
            populated which will be a bool. Bool populated is to check on if
            the cell has been given a specific type yet.
        5 - Must contain a 3 dimensional array of typedef CellRec, named Cube3DArr


    EXCEPTION HANDLING/ERROR CHECKING:
        1 - OutOfBoundsException thrown when invalid location is sent in
        2 - EmptyTypeException thrown when GetType is called on a cell with no specified type

                           SUMMARY OF METHODS:
    PUBLIC METHODS
        CubeClass() - Instantiates the class object to default values.
                      populated and status get set to false in every cell.
        CubeClass(*IN*const CellType& typeOfCell,
                  *IN*const bool& state);
                  -  Instantiates the class object to specified values for every cell's
                     status and celltype data members
                     Every cell's populated datatype gets set to true
        bool GetStatus(*IN*const LocationRec& cell) const - Gets the status of a cell
        void SetStatus(*IN*const LocationRec& cell,
                       *IN*const bool& stat) - Sets the status of a cell
        CellType GetType(*IN*const LocationRec& cell) const - Gets the CellType of the specified cell
        void SetType(*IN*const LocationRec& cell,
                     *IN*const CellType& currType) - Sets the CellType of the specified cell
        bool CubeStatus() const - Checks the status of the cube
        bool CubePopStatus() const - Checks the population status of the cube

    PRIVATE MEMBERS:
        Cube3DArr cubeArr; // The cube containing the cell's information

        bool InvalidLocation(*IN*const LocationRec& cell) const - Checks if the cell location is valid

*/

#include "Cellrec.h"	// SUPPLIED BY THE CLIENT
// Header which contains details of the cube record
#include "CubeExceptions.h" // For Cube Exception Classes

using namespace std;




class CubeClass
{
public:

    // O(N^3) : Default Constructor
    // Purpose: Instantiates the class object to default values.
    //          populated and status get set to false in every cell.
    // Pre: None
    // Post: Populated is set to false in every cell
    //       Status is set to false in every cell
    CubeClass();


    // O(N^3) : Non-Default Constructor
    // Purpose: Instantiates the class object to specified values for every cell's
    //          status and celltype data members
    //          Every cell's populated datatype gets set to true
    // Pre: The desired values for all cell's CellType and status
    // Post: Populated gets set to true
    //       status and CellType are set to their desired values
    CubeClass(/*IN*/const CellType& typeOfCell,     // The desired CellType
              /*IN*/const bool& state);              // The desired status value


    // O(1) : Observer Accessor
    // Purpose: Checks the status of a cell
    // Pre: Cube Exist, the location of the cell who's status is being returned
    // Post: Return true if the cell has been checked, otherwise false
    // Exception: OutOfBoundsException is thrown if the desired cell location is not within the cube
    bool GetStatus(/*IN*/const LocationRec& cell) const;    // The desired cell location


    // O(1) : Mutator
    // Purpose: Sets the status of a cell
    // Pre: Cube Exist, the location of the cell who's status is being changed,
    //                  the desired status
    // Post: Sets the status of the cell to the desired status
    // Exception: OutOfBoundsException is thrown if the desired cell location is not within the cube
    void SetStatus(/*IN*/const LocationRec& cell,    // The desired cell location
                   /*IN*/const bool& stat);          // The desired status


    // O(1) : Observer Accessor
    // Purpose: Gets the CellType of the specified cell
    // Pre: Cube Exist, the location of the cell
    // Post: The cell's CellType is returned
    // Exception: EmptyTypeException is thrown if the cell has no current type
    //            OutOfBoundsException is thrown if the desired cell location is not within the cube
    CellType GetType(/*IN*/const LocationRec& cell) const;    // The desired cell location


    // O(1) : Mutator
    // Purpose: Sets the CellType of the specified cell
    // Pre: Cube Exist, the desired cell and the CellType
    // Post: The cell's CellType is updated to the desired cell type,
    //       if the cell had no prior type, populated gets set to true for that cell
    // Exception: OutOfBoundsException is thrown if the desired cell location is not within the cube
    void SetType(/*IN*/const LocationRec& cell,    // The desired cell location
                /*IN*/const CellType& currType); // The desired type of the cell


    // O(N^3) : Observer Summarizer
    // Purpose: Checks the status of the cube
    // Pre: Cube Exist
    // Post: Return true if every cell has been checked, otherwise false
    bool CubeStatus() const;


    // O(N^3) : Observer Summarizer
    // Purpose: Check the population status of the cube
    // Pre: Cube Exist
    // Post: Return true if every cell has been populated, otherwise false
    bool CubePopStatus() const;


private:

    // PDMs
    Cube3DArr cubeArr; // The cube containing the cell's information


    // O(1) : Observer Predicator
    // Purpose: Checks if the cell location is valid
    // Pre: Cube Exist
    // Post: Return true if the location is invalid, otherwise false
    bool InvalidLocation(/*IN*/const LocationRec& cell) const;   // The desired cell location

}; // end CubeClass