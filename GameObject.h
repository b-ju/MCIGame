#pragma once
#include <string>

using namespace std;

//#SimonM A parent class that contains common fields for game objects
class GameObject
{
private:

	// ID value for the picture used to draw this object
	// *** Changed from ID String to pictureID into to pass what picture we are loading to graphics
	int pictureID;

	//height of object in pixels
	int height;

	//width of object in pixels
	int width;

	//x-axis location
	int xLocation;

	//y-axis location
	int yLocation;

	//speed at which the object moves
	double speed;
	

public:
	//Constructor
	GameObject( );

	//getters
	int getHeight( );
	int getWidth( );
	int getX( );
	int getY( );
	double getSpeed( );
	int getPictureID( ); // *** Changed from ID String to pictureID int

	//setters
	void setHeight( int h );
	void setWidth( int w );
	void setX( int x );
	void setY( int y );
	void setSpeed( double newSpeed );
	void setPictureID( int pictureID ); // *** Changed from ID String to pictureID int
};

