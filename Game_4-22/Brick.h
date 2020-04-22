#pragma once
#include "GameObject.h"

//#SimonM Object class for Brick objects

class Brick : public GameObject
{
private:
	//denotes the ID of the powerup in a given brick
	int powerupID;

public:
	//Constructor
	Brick( );

	//getters/setters
	int getPowerupID( );
	void setPowerupID( int powerup );
};

