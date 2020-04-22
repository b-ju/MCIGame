#pragma once
#include <SDL.h>
#include <iostream>
#include <string>

using namespace std;

class Level
{
	
	
	//*** Adding Picture ID to level for background images
	int pictureID; // ID value for background image.

	void develop( );

public:
	int getPictureID( ) { return pictureID; }
	void setPictureID( int pictureID ) { this->pictureID = pictureID; }
};

