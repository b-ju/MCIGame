#pragma once
#include <SDL.h>
#include <string>
#include <iostream>
using namespace std;

// A class designed to handle the details of texture use in SDL2
class TrelTexture
{
private:
	int picWidth;
	int picHeight;
	SDL_Texture* picTexture;	// The image

public:
	// Constructor
	TrelTexture( );
	// Deallocates memory
	~TrelTexture( );
	// loads image from file path
	bool loadFromFile( string fileName, SDL_Renderer* gRenderer );

	bool loadFromFileColor( string fileName, SDL_Renderer* gRenderer, Uint8 r, Uint8 g, Uint8 b );

	// Deallocates texture
	void free( );
	// renders texture at given location
	void render( int x, int y, SDL_Renderer* gRenderer, double angle=0, SDL_RendererFlip flip=SDL_FLIP_NONE, SDL_Point* center = NULL );
	void renderResize( int x, int y, SDL_Renderer* gRenderer, int w, int h, double angle = 0, SDL_RendererFlip flip = SDL_FLIP_NONE, SDL_Point* center = NULL );
	// gets image dimentions
	int getWidth( );
	int getHeight( );
	void setColor( Uint8 red, Uint8 green, Uint8 blue );
};
