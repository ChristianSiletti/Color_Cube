#include "Cube.h"	// Specification file for the Cube class	


// Pre: None
// Post: Populated is set to false in every cell
//       Status is set to false in every cell
CubeClass::CubeClass()
{
	// Cycle through each cell
	for (int i = 0; i < MAX_ROW; i++)
		for (int j = 0; j < MAX_COL; j++)
			for (int k = 0; k < MAX_DEP; k++)
			{
				// Populated and Status get set to false
				cubeArr[i][j][k].populated = false;
				cubeArr[i][j][k].status = false;
			}

}// end DC



// Pre: The desired values for all cell's CellType and status
// Post: Populated gets set to true
//       status and type are set to their desired values
CubeClass::CubeClass(/*IN*/const CellType& typeOfCell,     // The desired CellType
					 /*IN*/const bool& state)             // The desired status value
{
	// Cycle through each cell
	for (int i = 0; i < MAX_ROW; i++)
		for (int j = 0; j < MAX_COL; j++)
			for (int k = 0; k < MAX_DEP; k++)
			{
				// Populated gets set to true
				cubeArr[i][j][k].populated = true;
				// Status and type get their desired values
				cubeArr[i][j][k].status = state;
				cubeArr[i][j][k].type = typeOfCell;
			}

}// end NDC



// Pre: Cube Exist, the location of the cell who's status is being returned
// Post: Return true if the cell has been checked, otherwise false
// Exception: OutOfBoundsException is thrown if the desired cell location is not within the cube
bool CubeClass::GetStatus(/*IN*/const LocationRec& cell) const   // The desired cell location
{
	// Check to see if the cell location is valid
	if (InvalidLocation(cell))
		throw OutOfBoundsException();

	// returns the status of the current cell
	return cubeArr[cell.x][cell.y][cell.z].status;
}// end GetStatus



// Pre: Cube Exist, the location of the cell who's status is being changed,
//                  the desired status
// Post: Sets the status of the cell to the desired status
// Exception: OutOfBoundsException is thrown if the desired cell location is not within the cube
void CubeClass::SetStatus(/*IN*/const LocationRec& cell,    // The desired cell location
						  /*IN*/const bool& stat)          // The desired status
{
	// Check to see if the cell location is valid
	if (InvalidLocation(cell))
		throw OutOfBoundsException();

	// Set status to the desired value
	cubeArr[cell.x][cell.y][cell.z].status = stat;
}// end SetStatus



// Pre: Cube Exist, the location of the cell
// Post: The cell's CellType is returned
// Exception: EmptyTypeException is thrown if the cell has no current type
// Exception: OutOfBoundsException is thrown if the desired cell location is not within the cube
CellType CubeClass::GetType(/*IN*/const LocationRec& cell) const    // The desired cell location
{
	// Check to see if the cell location is valid
	if (InvalidLocation(cell))
		throw OutOfBoundsException();

	// Check to see if the current cell has a type yet
	if (cubeArr[cell.x][cell.y][cell.z].populated == false)
		throw EmptyTypeException();		// Throw an exception if it doesn't

	// Return the cell's type
	else
		return cubeArr[cell.x][cell.y][cell.z].type;

}// end GetType



// Pre: Cube Exist, the desired cell and the  CellType
// Post: The cell's CellType is updated to the desired cell type,
//       if the cell had no prior type, populated gets set to true for that cell
// Exception: OutOfBoundsException is thrown if the desired cell location is not within the cube
void CubeClass::SetType(/*IN*/const LocationRec& cell,    // The desired cell location
						/*IN*/const CellType& currType) // The desired type of the cell
{
	// Check to see if the cell location is valid
	if (InvalidLocation(cell))
		throw OutOfBoundsException();

	// Set the cell to the new CellType
	cubeArr[cell.x][cell.y][cell.z].type = currType;

	// Update the cell to have a CellType
	cubeArr[cell.x][cell.y][cell.z].populated = true;
}// end SetType



// Pre: Cube Exist
// Post: Return true if every cell has been checked, otherwise false
bool CubeClass::CubeStatus() const
{
	// Cycle through each cell
	for (int i = 0; i < MAX_ROW; i++)
		for (int j = 0; j < MAX_COL; j++)
			for (int k = 0; k < MAX_DEP; k++)
			{
				// Check to see if the cell has not been checked
				if (!cubeArr[i][j][k].status)
					return false;	// return false, the cube is not fully checked yet!
			}
	// Every cell has been checked
	return true;
}// end CubeStatus



// Pre: Cube Exist
// Post: Return true if every cell has been populated, otherwise false
bool CubeClass::CubePopStatus() const
{
	// Cycle through each cell
	for (int i = 0; i < MAX_ROW; i++)
		for (int j = 0; j < MAX_COL; j++)
			for (int k = 0; k < MAX_DEP; k++)
			{
				// Check to see if the cell has not been populated
				if (!cubeArr[i][j][k].populated)
					return false;	// return false, the cube is not fully poulated yet!
			}
	// Every cell has been populated
	return true;

}// end CubePopStatus



// Pre: Cube Exist
// Post: Return true if the location is invalid, otherwise false
bool CubeClass::InvalidLocation(/*IN*/const LocationRec& cell) const   // The desired cell location
{
	if (cell.x >= MAX_ROW || cell.x < ZERO || cell.y >= MAX_COL ||
		cell.y < ZERO || cell.z >= MAX_DEP || cell.z < ZERO)
		return true;

	return false;
}// end InvalidLocation