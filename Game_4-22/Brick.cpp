#include "Brick.h"
// Team: Logic
// Author: Simon Martin


//Child class of GameObject for Brick objects

/***********************************************************
#SimonM
Name: Brick
Description: Constructor
**********************************************************/
Brick::Brick( )
{
	GameObject( );
	powerupID = -1;
	// This needs width and height to be set. 
}

/***********************************************************
#SimonM
Name: getPowerupID
Description: getter, returns powerupID
**********************************************************/
int Brick::getPowerupID( )
{
	return powerupID;
}

/***********************************************************
#SimonM
Name: setPowerupID
Description: setter, takes int parameter and sets to powerupID
**********************************************************/
void Brick::setPowerupID( int powerup )
{
	this->powerupID = powerup;
}