#include "GraphicsMethods.h"
//written by Trel J

/*************************
name: drawFlatScreen
description: ** this is a prototpye some things will be changed **
	Adds pictures from Brick,Ball,Paddle, and Level objects to frame rotation.
Comments Updated: Ben Jurenka
**************************/

void drawFlatScreen( std::vector<Brick> bricks, std::vector<Ball> balls, Paddle paddle, Level background )
{
	static TrelGraphics2 brickPictures( "brickpictures.txt", 0xFF, 0xFF, 0xFF );
	static TrelGraphics2 ballPictures( "ballpictures.txt", 0xFF, 0xFF, 0xFF );
	static TrelGraphics2 paddlePictures( "paddlepictures.txt", 0xFF, 0xFF, 0xFF );
	static TrelGraphics2 backgroundPictures( "backgroundpictures.txt" );
	int x, y, w, h;
	double angle;
	bool vFlip, hFlip;
	SDL_Point center;
	backgroundPictures.addPictureToFrame( background.getPictureID( ), 0, 0 );
	for ( Brick brick : bricks )
	{
		w = brick.getWidth( );	// This is working under the assumtion that getWidth returns the distance to the edge from the center.
		h = brick.getHeight( ); // This is working under the assumtion that getHeight returns the distance to the edge from teh center.
		x = brick.getX( ) - w; //*** removed Center to match logic code
		y = brick.getY( ) - h;
		//angle = brick.getDirection( );  //*** commentted out as it's not used for other objects.
		angle = 0;
		//*** commenting out flipping and replacing with false as we are not doing that here.
		//vFlip = brick.getVFlip( );	// Temperory concept, likely to be replaced by math, will depend on art and logic team.
		//hFlip = brick.getHFlip( );	// ^
		vFlip = false;
		hFlip = false;
		//*** incorrect setup for SDL_Point, replacing center = (x + w, y + h);
		center.x = x + w;
		center.y = y + h;
		brickPictures.addPictureToFrameRotation( brick.getPictureID( ), x, y, angle, vFlip, hFlip, center );
	}
	//*** changes above repeated
	for ( Ball ball : balls )
	{
		w = ball.getWidth( );	// This is working under the assumtion that getWidth returns the distance to the edge from the center.
		h = ball.getHeight( ); // This is working under the assumtion that getHeight returns the distance to the edge from the center.
		x = ball.getX( ) - w;
		y = ball.getY( ) - h;
		//angle = ball.getDirection( );
		angle = 0;
		//vFlip = ball.getVFlip( );	// Temperory concept, likely to be replaced by math, will depend on art and logic team.
		//hFlip = ball.getHFlip( );	// ^
		vFlip = false;
		hFlip = false;
		//center = (x + w, y + h);
		center.x = x + w;
		center.y = y + h;
		ballPictures.addPictureToFrameRotation( ball.getPictureID( ), x, y, angle, vFlip, hFlip, center );
	}
	w = paddle.getWidth( );	// This is working under the assumtion that getWidth returns the distance to the edge from the center.
	h = paddle.getHeight( ); // This is working under the assumtion that getHeight returns the distance to the edge from teh center.
	x = paddle.getX( ) - w;
	y = paddle.getY( ) - h;
	//angle = paddle.getDirection( );
	angle = 0;
	//vFlip = paddle.getVFlip( );	// Temperory concept, likely to be replaced by math, will depend on art and logic team.
	//hFlip = paddle.getHFlip( );	// ^
	vFlip = false;
	hFlip = false;
	//center = (x + w, y + h);
	center.x = x + w;
	center.y = y + h;
	paddlePictures.addPictureToFrameRotation( paddle.getPictureID( ), x, y, angle, vFlip, hFlip, center );
	TrelGraphics2::drawFrame( );
}

/*************************
name: drawCircularScreen
description: ** this is a prototpye some things will be changed **
	Adds pictures from Brick,Ball,Paddle, and Level objects to frame rotation.
Comments Updated: Ben Jurenka
**************************/
void drawCircularScreen( std::vector<Brick> bricks, std::vector<Ball> balls, Paddle paddle, Level background )
{
	cout << "***** This method has not been built yet"<< endl; 
}


/********************************************************
name: drawTitleScreen
description: creates a static TrelGraphics2 object that holds
		 one texture loaded from text stored in titleImage.txt file
		 adds title image to window.
**********************************************************/
void drawTitleScreen( )
{
	static TrelGraphics2 titleImage( "titleImage.txt" );// Best way to handle it, not worth making a new constructor for one image, and doing seperalty is a bad idea with static local variables
	titleImage.addPictureToFrame( 0, 0, 0 );
	TrelGraphics2::drawFrame( );
}
