#include "TrelGraphics2.h"
// Team: Graphics
// comments updated by #Nick Brady , #Ben Jurenka


SDL_Renderer* TrelGraphics2::gRenderer = NULL;			
SDL_Window* TrelGraphics2::gWindow = NULL;
int TrelGraphics2::windowWidth = 0;
int TrelGraphics2::windowHeight = 0;
 
/***********************************************************
Name: start
Description: Initializes SDL, Opens a window and sets window title/width/height,
and starts the renderer,must be called at the start of main.
Written By: Trel Johnson
***********************************************************/

void TrelGraphics2::start( string windowTitle, int width, int height )
{
    if ( gRenderer != NULL || gWindow != NULL )
    {
        cout << "Window or renderer already exist, call method close() before calling this method again." << endl;
        return;
    }
    windowWidth = width;
    windowHeight = height;
    if ( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        cout << "SDL did not initialize" << endl;
    }
    else
    {
        gWindow = SDL_CreateWindow( windowTitle.c_str( ), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, windowWidth, windowHeight, SDL_WINDOW_SHOWN );
        if ( gWindow == NULL )
        {
            cout << "Window could not be created" << endl;
        }
        else
        {
            gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
            if ( gRenderer == NULL )
            {
                cout << "Renderer could not be created" << endl;
            }
            else
            {
                SDL_SetRenderDrawBlendMode( gRenderer, SDL_BLENDMODE_BLEND );
                SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
                SDL_RenderClear( gRenderer );
                SDL_RenderPresent( gRenderer );
            }
        }
    }
}


/***********************************************************
Name: close
Description: closes renderer, window, and SDL and frees their memory, 
must be called at the end of main.
Written By: Trel Johnson
***********************************************************/

void TrelGraphics2::close( )
{
    SDL_DestroyRenderer( gRenderer );
    SDL_DestroyWindow( gWindow );
    gWindow = NULL;
    gRenderer = NULL;
    SDL_Quit( );
}


/***********************************************************
Name:TrelGraphics2
Description: Creates a TrelGraphics2 object and assigns memory for size number of images.
Written By: Trel Johnson
***********************************************************/

TrelGraphics2::TrelGraphics2( int size )
{
    this->size = size;
    textures = new TrelTexture[size];
    index = 0;
}


/***********************************************************
Name:TrelGraphics2
Description: Creates a TrelGraphics2 object, reads an image list text file, assigns memory for them all and loads them all.
Written By: Trel Johnson
***********************************************************/

TrelGraphics2::TrelGraphics2( string fileName )
{
    ifstream readFile;
    readFile.open( fileName.c_str( ) );
    string toOpen;
    int counter = 0;
    getline( readFile, toOpen );
    while ( readFile )
    {
        counter++;
        getline( readFile, toOpen );
    }
    readFile.close( );
    size = counter;
    textures = new TrelTexture[size];
    index = 0;
    readImageListFromFile( fileName );
}


/***********************************************************
Name:TrelGraphics2
Description: Creates a TrelGraphics2 object, reads an image list text file, assigns memory for them all and loads them all, then color keys them to given colors, 
Written By: Trel Johnson
***********************************************************/

TrelGraphics2::TrelGraphics2( string fileName, Uint8 r, Uint8 g, Uint8 b )
{
    ifstream readFile;
    readFile.open( fileName.c_str( ) );
    string toOpen;
    int counter = 0;
    getline( readFile, toOpen );
    while ( readFile )
    {
        counter++;
        getline( readFile, toOpen );
    }
    readFile.close( );
    size = counter;
    textures = new TrelTexture[size];
    index = 0;
    readImageListFromFileColor( fileName, r, g, b );
}


/***********************************************************
Name:TrelGraphics2
Description: Closes the TrelGraphics2 object and deletes all the assigned memory, 
must be called at the end of the program. This should be all that's needed for all 
memory allocated to be deleted.
Written By: Trel Johnson
***********************************************************/

TrelGraphics2::~TrelGraphics2( )
{
    delete[] textures;

}


/***********************************************************
Name:CreatePictureFromFile
Description: creates a picture from a file, and returns it's pictureID
Written By: Trel Johnson
***********************************************************/

int TrelGraphics2::createPictureFromFile( string fileName )
{
    if ( index >= size )
    {
        cout << "ERROR: loading more images than spaces were assigned, assign more space to this object." << endl;
        return -1;
    }
    textures[index]= TrelTexture( ) ;
    textures[index].loadFromFile( fileName, gRenderer );
    index++;
    return index-1;
}


/***********************************************************
Name:createPictureFromFileColor
Description: same as createPictureFromFilebut will set the color key 
for transparency to the given r,g,b values r,g,b must be from 0 to 255.
Written By: Trel Johnson
***********************************************************/

int TrelGraphics2::createPictureFromFileColor( string fileName, Uint8 r, Uint8 g, Uint8 b )
{
    if ( index >= size )
    {
        cout << "ERROR: loading more images than spaces were assigned, assign more space to this object." << endl;
        return -1;
    }
    textures[index] = TrelTexture( );
    textures[index].loadFromFileColor( fileName, gRenderer, r, g, b );
    index++;
    return index - 1;
}


/***********************************************************
Name:readImageListFromFile
Description: reads a file and opens images writen in that file until file is done 
or assigned memory is reached
Written By: Trel Johnson
***********************************************************/

void TrelGraphics2::readImageListFromFile( string fileName )
{
    ifstream readFile;
    readFile.open( fileName.c_str( ) );
    string toOpen;
    getline( readFile, toOpen );
    while ( readFile && index<size )
    {
        createPictureFromFile( toOpen );
        getline( readFile, toOpen );
    }
    readFile.close( );
}


/***********************************************************
Name:readImageListFromFile
Description: same as readImageListFromFile(string) but will set the color key for transparency 
to the given r,g,b values. r,g,b must be from 0 to 255
Written By: Trel Johnson
***********************************************************/

void TrelGraphics2::readImageListFromFileColor( string fileName, Uint8 r, Uint8 g, Uint8 b )
{
    ifstream readFile;
    readFile.open( fileName.c_str( ) );
    string toOpen;
    getline( readFile, toOpen );
    while ( readFile && index < size )
    {
        createPictureFromFileColor( toOpen, r, g, b );
        getline( readFile, toOpen );
    }
    readFile.close( );
}


/**********************************************************
name: addPictureToFrame
description:adds a picture to a frame, but does not draw it, call drawFrame() to draw all     pictures on frame.
    pictureId = index of picture to add
    x,y 
Written By: Trel Johnson
**********************************************************/

void TrelGraphics2::addPictureToFrame( int pictureID, int x, int y )
{
    if ( pictureID >= index || pictureID < 0 )
    {
        return;
    }
    textures[pictureID].render( x, y, gRenderer );
}


/**********************************************************
name: addPictureToFrameResize
description: adds a picture to a frame, but does not draw it, call drawFrame() to draw all     pictures on frame.
    x,y = where the top left corner of rectangle will be placed on screen
    w,h = resized demensions, w is horizontal change, h is vertical change
Written By: Trel Johnson
**********************************************************/

void TrelGraphics2::addPictureToFrameResize( int pictureID, int x, int y, int w, int h )
{
    if ( pictureID >= index || pictureID < 0 )
    {
        return;
    }
    textures[pictureID].renderResize( x, y, gRenderer, w, h );
}


/**********************************************************
name: addPicturetoFrameRotation
description: adds a picture to a frame, but does not draw it, call drawFrame() to draw all pictures on frame. Allows for roation and flipping of image.
Written By: Trel Johnson
**********************************************************/

void TrelGraphics2::addPicturetoFrameRotation( int pictureID, int x, int y, double degrees, bool vFlip, bool hFlip )
{
    if ( pictureID >= index || pictureID < 0 )
    {
        return;
    }
    SDL_RendererFlip flip=SDL_FLIP_NONE;
    if ( !hFlip && vFlip )
    {
        flip = SDL_FLIP_VERTICAL;
    }
    if ( !vFlip && hFlip )
    {
        flip = SDL_FLIP_HORIZONTAL;
    }
    if ( vFlip && hFlip )
    {
        flip = (SDL_RendererFlip) (SDL_FLIP_HORIZONTAL | SDL_FLIP_VERTICAL);
    }
    textures[pictureID].render( x, y, gRenderer, degrees, flip );
}


/**********************************************************
name: addRectToFrame
description: adds a rectangle to the frame with the given color and transparancy
               x,y = where the top left corner of rectangle will be placed on screen
               w,h = width/height of rect
               filled = true for a filled rectanle, false for outline of rect
Written By: Trel Johnson
**********************************************************/

void TrelGraphics2::addRectToFrame( int x, int y, int w, int h, Uint8 r, Uint8 g, Uint8 b, Uint8 a, bool filled )
{
    SDL_Rect draw{ x,y,w,h };
    SDL_SetRenderDrawColor( gRenderer, r, g, b, a );
    if ( filled )
    {
        SDL_RenderFillRect( gRenderer, &draw );
    }
    else
    {
        SDL_RenderDrawRect( gRenderer, &draw );
    }
    SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
}


/**********************************************************
 name: drawFrame
 description: draws frame to screen
 Written By: Trel Johnson
 **********************************************************/
 
void TrelGraphics2::drawFrame( )
{
    SDL_RenderPresent( gRenderer );
}


/**********************************************************
 name: clearFrame
 description: clears the frame to a white image
 Written By: Trel Johnson
**********************************************************/

void TrelGraphics2::clearFrame( )
{
    SDL_RenderClear( gRenderer );
}


/**********************************************************
 name: getArraySize
 description: returns number of images allowed to be created
 Written By: Trel Johnson
***********************************************************/

int TrelGraphics2::getArraySize( )
{
    return size;
}


/*********************************************************
 name: getNumberOfImages
 description: returns number of loaded images
 Written By: Trel Johnson
*********************************************************/

int TrelGraphics2::getNumberOfImages( )
{
    return index - 1;
}


/*********************************************************
name: getImageWidth
description: getters for image width/height
            pictureId = index of picture
Written By: Trel Johnson
*********************************************************/

int TrelGraphics2::getImageWidth( int pictureID )
{
    if ( pictureID < index || pictureID >= 0 )
    {
        return textures[pictureID].getWidth( );
    }
    return -1;
}

int TrelGraphics2::getImageHeight( int pictureID )
{
    if ( pictureID < index && pictureID >= 0 )
    {
        return textures[pictureID].getHeight( );
    }
    return -1;
}


/*********************************************************
name:setPictureColor
description:set an additional color value multiplied into 
render copy operations of the specified, from pictureID, texture
Written By: Trel Johnson
**********************************************************/

void TrelGraphics2::setPictureColor( int pictureID, Uint8 red, Uint8 green, Uint8 blue )
{
    textures[pictureID].setColor( red, green, blue );
}

