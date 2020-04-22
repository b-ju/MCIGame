//Main Driver for MCI Game - version 1
//starts, plays and ends the game
//written by: Patty Wiens 4/18/20
//edited by:  Trel Johnson, Nick Brady 4/22




//# include "SDL_mixer.h" // commenting out mixer untill implementation needs to happen 

// Implemented Driver.h to remove having to include more than 1 .h file
#include "Driver.h"


using namespace std;


void startGame( );
void endGame( );
void playGame( );

vector<Brick> bricks;
vector<Ball> balls;
Paddle paddle;
Level level; //*** exists to make me not have to delete stuff from drawScreen();


int main( int argc, char** argv ) // Main must have these specific arguments for SDL to work 
{

	
	startGame( );
	playGame( );
	endGame( );
	


	system( "pause" );
	return 0;
}


//*** moved game.cpp over to here


void startGame( )
{
	
	TrelGraphics2::start( "Insert MCI Game Name Here", 700, 500 ); //*** needed a TrelGraphics::start call, made up a size.
	cout << "in Gamemain startGame - NEEDS TO BE IMPLEMENTED" << endl;
	
	//** This code probably belongs in level? 
	Brick temp1;
	temp1.setX( 300 );
	temp1.setY( 30 );
	bricks.push_back( temp1 );
	Ball temp2;
	temp2.setX( 400 );
	temp2.setY( 200 );
	balls.push_back( temp2 );
	paddle.setX( 350 );
	paddle.setY( 450 );
	level.setPictureID( 0 );
}

void playGame( )
{
	cout << "in Gamemain playGame - NEEDS TO BE IMPLEMENTED" << endl;

	bool quit = false;
	int direction = 0;
	SDL_Event e;
	while ( !quit )
	{
		while ( SDL_PollEvent( &e ) != 0 )
		{
			if ( e.type == SDL_QUIT )
			{
				quit = true;
			}
			else if ( e.type == SDL_KEYDOWN )
			{
				switch ( e.key.keysym.sym )
				{
				case SDLK_LEFT:
					direction = -1;
					break;
				case SDLK_RIGHT:
					direction = 1;
					break;
				case SDLK_1:
					level.setPictureID( 0 );
					break;
				case SDLK_2:
					level.setPictureID( 1 );
					break;
				case SDLK_3:
					level.setPictureID( 2 );
					break;

				}
			}
			else if ( e.type == SDL_KEYUP )
			{
				switch ( e.key.keysym.sym )
				{
				case SDLK_LEFT:
					direction = direction == 1 ? 1 : 0;
					break;
				case SDLK_RIGHT:
					direction = direction == -1 ? -1 : 0;
					break;
				}
			}
		}

		// removed draw code. Draw Flat screen needs to be used to draw things to the screen 
		drawFlatScreen( bricks, balls, paddle, level );
	}

}

void endGame( )
{
	cout << "in gameMain endGame - NEEDS TO BE IMPLEMENTED" << endl;
	TrelGraphics2::close( );

}


