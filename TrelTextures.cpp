#include "TrelTexture.h"
// Team: Graphics
// comments updated by #Nick Brady , #Ben Jurenka


// A class designed to handle the details of texture use in SDL2 - Graphics Team

/***********************************************************
Name: TrelTexture
Description: Constructor
**********************************************************/

TrelTexture::TrelTexture( )
{
    picTexture = NULL;
    picWidth = 0;
    picHeight = 0;
}

// Deallocates memory
TrelTexture::~TrelTexture( )
{
    free( );
}


/***********************************************************
Name: loadFromFile
Description: loads image from file path
Written By: Trel Johnson
***********************************************************/

bool TrelTexture::loadFromFile( std::string fileName, SDL_Renderer* gRenderer )
{
    free( );
    SDL_Texture* newTexture = NULL;
    SDL_Surface* loadedSurface = SDL_LoadBMP( fileName.c_str() );
    if ( loadedSurface == NULL )
    {
        cout << "image could not load" << endl;
    }
    else
    {
        newTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
        if ( newTexture == NULL )
        {
            cout << "texture could not be created" << endl;
        }
        else
        {
            picWidth = loadedSurface->w;
            picHeight = loadedSurface->h;
        }
        SDL_FreeSurface( loadedSurface );
    }
    picTexture = newTexture;
    return picTexture != NULL;

}


/***********************************************************
Name: loadFromFile
Description: loads image from file path, additionally sets the 
color key of the pixel that needs to be transparent
Written By: Trel Johnson
***********************************************************/

bool TrelTexture::loadFromFileColor( string fileName, SDL_Renderer* gRenderer, Uint8 r, Uint8 g, Uint8 b )
{
    free( );
    SDL_Texture* newTexture = NULL;
    SDL_Surface* loadedSurface = SDL_LoadBMP( fileName.c_str( ) );
    if ( loadedSurface == NULL )
    {
        cout << "image could not load" << endl;
    }
    else
    {
        SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, r, g, b ));
        newTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
        if ( newTexture == NULL )
        {
            cout << "texture could not be created" << endl;
        }
        else
        {
            picWidth = loadedSurface->w;
            picHeight = loadedSurface->h;
        }
        SDL_FreeSurface( loadedSurface );
    }
    picTexture = newTexture;
    return picTexture != NULL;

}


/***********************************************************
Name: TrelTexture::Free
Description: Deallocates texture
Written By: Trel Johnson
***********************************************************/

void TrelTexture::free( )
{
    if ( picTexture != NULL )
    {
        SDL_DestroyTexture( picTexture );
        picTexture = NULL;
        picWidth = 0;
        picHeight = 0;
    }
}


/*********************************************************
name: render
description: renders texture at given location
    x,y = position where top left corner of texture will be placed
    degrees = the degree to rotate the image
    flip = enum to horizontal and/or vertically flip
    center = point to rotate image
Written By: Trel Johnson
*********************************************************/

void TrelTexture::render( int x, int y, SDL_Renderer* gRenderer, double degrees, SDL_RendererFlip flip, SDL_Point* center )
{
    SDL_Rect renderQuad = { x,y,picWidth, picHeight };
    SDL_RenderCopyEx( gRenderer, picTexture, NULL, &renderQuad, degrees, center, flip );
}


/*********************************************************
name: renderResize
description: resize an image and renders texture at given location
    x,y = position where top left corner of texture will be placed
    w,h = the width/height to resize the image to
    degrees = the degree to rotate the image
    flip = enum to horizontal and/or vertically flip
    center = point to rotate image 
Written By: Trel Johnson
*********************************************************/

void TrelTexture::renderResize( int x, int y, SDL_Renderer* gRenderer, int w, int h, double degrees, SDL_RendererFlip flip, SDL_Point* center )
{
    SDL_Rect renderQuad = { x,y,w, h };
    SDL_RenderCopyEx( gRenderer, picTexture, NULL, &renderQuad, degrees, center, flip );
}


/*********************************************************
name: getWidth - getHeight
description: getters for width/ height
Written By: Trel Johnson
*********************************************************/
int TrelTexture::getWidth( )
{
    return picWidth;
}

int TrelTexture::getHeight( )
{
    return picHeight;
}


/*********************************************************
name: setColor
description: set an additional color value multiplied into render copy 
operations of the specified Trel::Texture (specified from pictureID) 
Written By: Trel Johnson
***********************************************************/

void TrelTexture::setColor( Uint8 red, Uint8 green, Uint8 blue )
{
    //Modulate texture
    SDL_SetTextureColorMod( picTexture, red, green, blue );
}
