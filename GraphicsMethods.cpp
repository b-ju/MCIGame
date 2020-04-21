#include "GraphicsMethods.h" //written by Trel J
/*************************
name: drawScreen
description: ** this is a prototpye some things will be changed **
	Adds pictures from Brick,Ball,Paddle, and Level objects to frame rotation.
Comments Updated: Ben Jurenka
**************************/

void drawScreen( std::vector<Brick> bricks, std::vector<Ball> balls, Paddle paddle, Level background )
{
	static TrelGraphics2 brickPictures( "brickpictures.txt" );
	static TrelGraphics2 ballPictures( "ballpictures.txt" );
	static TrelGraphics2 paddlePictures( "paddlepictures.txt" );
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
		x = brick.getCenterX( ) - w;
		y = brick.getCenterY( ) - h;
		angle = brick.getDirection( );
		vFlip = brick.getVFlip( );	// Temperory concept, likely to be replaced by math, will depend on art and logic team.
		hFlip = brick.getHFlip( );	// ^
		center = ( x + w, y + h );
		brickPictures.addPictureToFrameRotation( brick.getPicID( ), x, y, angle, vFlip, hFlip, center );
	}
	for ( Ball ball : balls )
	{
		w = ball.getWidth( );	// This is working under the assumtion that getWidth returns the distance to the edge from the center.
		h = ball.getHeight( ); // This is working under the assumtion that getHeight returns the distance to the edge from the center.
		x = ball.getCenterX( ) - w;
		y = ball.getCenterY( ) - h;
		angle = ball.getDirection( );
		vFlip = ball.getVFlip( );	// Temperory concept, likely to be replaced by math, will depend on art and logic team.
		hFlip = ball.getHFlip( );	// ^
		center = (x + w, y + h);
		ballPictures.addPictureToFrameRotation( ball.getPicID( ), x, y, angle, vFlip, hFlip, center );
	}
	w = paddle.getWidth( );	// This is working under the assumtion that getWidth returns the distance to the edge from the center.
	h = paddle.getHeight( ); // This is working under the assumtion that getHeight returns the distance to the edge from teh center.
	x = paddle.getCenterX( ) - w;
	y = paddle.getCenterY( ) - h;
	angle = paddle.getDirection( );
	vFlip = paddle.getVFlip( );	// Temperory concept, likely to be replaced by math, will depend on art and logic team.
	hFlip = paddle.getHFlip( );	// ^
	center = (x + w, y + h);
	paddlePictures.addPictureToFrameRotation( paddle.getPicID( ), x, y, angle, vFlip, hFlip, center );
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
}
