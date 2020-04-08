// Concept for brick break draw method written by Trel Johnson
// #updated by Ben Jurenka
#include "TrelGraphics2.h"


// global variables, these will be initialized in main or TrelGraphics2::start method
TrelGraphics2 ballPictures( "ballpictures.bmp" );
TrelGraphics2 paddlePictures( "paddlepictures.bmp" );
TrelGraphics2 brickPictures( "brickpictures.bmp" );
/***********************************************************
Name: drawGame
Description: renders balls, paddle, and bricks to screen.
Written By: Trel Johnson
***********************************************************/

void drawGame( std::vector<Ball> balls, Paddle paddle, std::vector<Brick> bricks )
{
	// these numbers are just there to exist, obviously will be changed to match actual values.
	// plenty of the math will be adjusted based on exact nature of some numbers and values.
	const static int BALL_WIDTH = 20;
	const static int BALL_HEIGHT = 20; 
	const static int PADDLE_WIDTH = 20;
	const static int PADDLE_HEIGHT = 20;
	const static int BRICK_WIDTH = 20;
	const static int BRICK_HEIGHT = 20;
	
    int x, y;       //variables for rendering at location on windown, reused for ball, brick, paddle
          
                    //add ball to renderer based on variables stored in ball object
	for ( Ball ball : balls )
	{
		x = ball.getCenterX( )-BALL_WIDTH;
		y = ball.getCenterY( )-BALL_HEIGHT;
		ballpictures.addPictureToFrameRotation( 0, x, y, ball.getDirection( ), false, false );
                    // doesn't include proper centering yet, will add that in final version
	}
                    //add paddle to renderer based on variables stored in paddle object
	x = paddle.getCenterX( ) - PADDLE_WIDTH;
	y = paddle.getCenterY( ) - PADDLE_HEIGHT;
	paddlePictures.addPictureToFrameRotation( 0, x, y, paddle.getDirection( ), false, false );
    
                    //add all bricks to renderer based on the variables stored in brick objects
    for ( Brick brick : bricks )
	{
		x = brick.getCenterX( ) - BRICK_WIDTH;
		y = brick.getCenterY( ) - BRICK_HEIGHT;
		brickPictures.addPictureToFrameRotation( 0, x, y, brick.getDirection( ), false, false );
	}
    
                    // Display all changes made
	TrelGraphics2::drawFrame( );
}
