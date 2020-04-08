#pragma once
#include <iostream>
#include <SDL.h>
#include <vector>
#include <string>
#include <fstream>
#include "TrelTexture.h"
using namespace std;

// A graphics object designed to handle the details of running SDL2. 
// start() and close() methods MUST be called at the start and end of main
// and main MUST have the parameters (int argc, char* args[]) and return an int.
class TrelGraphics2
{
private:
	TrelTexture* textures;		// the array for loaded pictures
	int size;		// the size of the textures array
	int index;		// assigned to be the number of the left most EMPTY array space.

	static SDL_Window* gWindow;		// the window loaded and printed to
	static SDL_Renderer* gRenderer;		// the renderer that handles texture printing
	static int windowWidth;			// ... I hope I don't need to explain this
	static int windowHeight;		// ... I hope I don't need to explain this

public:
	// Initializes SDL, Opens a window, and starts the renderer, must be called at the start of main.
	static void start( string windowTitle="No Window Title Given", int width=640, int height=480 );

	// closes renderer, window, and SDL and frees their memory, must be called at the end of main.
	static void close( );
	
	// Creates a TrelGraphics2 object and assigns memory for size number of images.
	TrelGraphics2( int size=10 );

	// Creates a TrelGraphics2 object, reads an image list text file, assigns memory for them all and loads them all.
	TrelGraphics2( string fileName );

	// Creates a TrelGraphics2 object, reads an image list text file, assigns memory for them all and loads them all.
	// Then color keys them to given colors
	TrelGraphics2( string fileName, Uint8 r, Uint8 g, Uint8 b );
	
	// Closes the TrelGraphics2 object and deletes all the assigned memory, must be called at the end of the program
	~TrelGraphics2( );

	// creates a picture from a file, and returns it's pictureID, can only load .bmp files
	int createPictureFromFile( string fileName );

    //same as createPictureFromFile  but will set the color key for transparency to the given
       // r,g,b values.
    // r,g,b must be from 0 to 255
	int createPictureFromFileColor( string fileName, Uint8 r, Uint8 g, Uint8 b );

	// reads a file and opens images writen in that file until file is done or assigned memory is reached
	void readImageListFromFile( string fileName );
    
    //same as reamImageListFromFile(string) but will set the color key for transparency to the given
    // r,g,b values.
    // r,g,b must be from 0 to 255
	void readImageListFromFileColor( string fileName, Uint8 r, Uint8 g, Uint8 b );

	// adds a picture to a frame, but does not draw it, call drawFrame() to draw all pictures on frame.
	void addPictureToFrame( int pictureID, int x, int y );

	// adds a picture to a frame, but does not draw it, call drawFrame() to draw all pictures on frame.
	void addPictureToFrameResize( int pictureID, int x, int y, int w, int h );

	// adds a picture to a frame, but does not draw it, call drawFrame() to draw all pictures on frame.
	// Allows for roation and flipping of image. 
	void addPicturetoFrameRotation( int pictureID, int x, int y, double degrees, bool vFlip, bool hFlip );

	// adds a rectangle to the frame with the given color and transparancy
	static void addRectToFrame( int x, int y, int w, int h, Uint8 r, Uint8 g, Uint8 b, Uint8 a, bool filled=true );

	// draws frame to screen
	static void drawFrame( );

	// clears the frame to a white image
	static void clearFrame( );

	// returns number of images allowed to be created
	int getArraySize( );

	// returns number of loaded images
	int getNumberOfImages( );

	// returns width of image at pictureID
	int getImageWidth( int picutreID );

	// returns hight of image at pictureID
	int getImageHeight( int pictureID );

    //set an additional color value multiplied into render copy operations of the specified(from pictureID) texture
	void setPictureColor( int pictureID, Uint8 red, Uint8 green, Uint8 blue );

};

