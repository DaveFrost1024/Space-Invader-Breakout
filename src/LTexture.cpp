#include <SDL2/SDL_image.h>
#include <iostream>
#include <string>

#include "LTexture.h"

LTexture::LTexture()
{
    mTexture = NULL;
    mWidth = 0;
    mHeight = 0;
}

LTexture::~LTexture()
{
    // deallocate
    free();
}

bool LTexture::loadFromFile( SDL_Renderer* gRenderer, std::string path )
{
    // release preexisting texture
    free();

    SDL_Texture* newTexture = NULL;

    // load image from path
    SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
    if( loadedSurface == NULL )
    {
        printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
    }
    else
    {
        // color key image
        SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0, 0xFF, 0xFF ) );

        // create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
        if( newTexture == NULL )
        {
            printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
        }
        else
        {
            // get image dimensions
            mWidth = loadedSurface->w;
            mHeight = loadedSurface->h;
        }

        // get rid of old loaded surface
        SDL_FreeSurface( loadedSurface );
    }

    mTexture = newTexture;
    return mTexture != NULL;
}

bool LTexture::loadFromFile( SDL_Renderer* gRenderer, std::string path, float dimensionX, float dimensionY )
{
    // release preexisting texture
    free();

    SDL_Texture* newTexture = NULL;

    // load image from path
    SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
    if( loadedSurface == NULL )
    {
        printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
    }
    else
    {
        // color key image
        SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0, 0xFF, 0xFF ) );

        // create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
        if( newTexture == NULL )
        {
            printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
        }
        else
        {
            // get image dimensions
            //mWidth = (int)((loadedSurface->w) * dimensionX);
            //mHeight = (int)((loadedSurface->h) * dimensionY);
            mWidth = (int) dimensionX;
            mHeight = (int) dimensionY;

        }

        // get rid of old loaded surface
        SDL_FreeSurface( loadedSurface );
    }

    mTexture = newTexture;
    return mTexture != NULL;
}

bool LTexture::loadFromRenderedText( SDL_Renderer* gRenderer, TTF_Font* gFont, std::string textureText, SDL_Color textColor )
{
    // release preexisting texture
    free();

    // render text surface
    SDL_Surface* textSurface = TTF_RenderText_Solid( gFont, textureText.c_str(), textColor );
    if( textSurface != NULL )
    {
        // create texture from surface pixels
        mTexture = SDL_CreateTextureFromSurface( gRenderer, textSurface );
        if( mTexture == NULL )
        {
            printf( "Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError() );
        }
        else
        {
            // get image dimensions
            mWidth = textSurface->w;
            mHeight = textSurface->h;
        }

        // get rid of old surface
        SDL_FreeSurface( textSurface );
    }
    else
    {
        printf( "Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError() );
    }
    
    return mTexture != NULL;
}

void LTexture::free()
{
    // free texture if it exists
    if( mTexture != NULL )
    {
        SDL_DestroyTexture( mTexture );
        mTexture = NULL;
        mWidth = 0;
        mHeight = 0;
    }
}

void LTexture::setColor( Uint8 red, Uint8 green, Uint8 blue )
{
    // modulate texture rgb
    SDL_SetTextureColorMod( mTexture, red, green, blue );
}

void LTexture::setBlendMode( SDL_BlendMode blending )
{
    // set blending function
    SDL_SetTextureBlendMode( mTexture, blending );
}
        
void LTexture::setAlpha( Uint8 alpha )
{
    // modulate texture alpha
    SDL_SetTextureAlphaMod( mTexture, alpha );
}

void LTexture::render( SDL_Renderer* gRenderer, int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip )
{
    // set rendering space and render to screen
    SDL_Rect renderQuad = { x, y, mWidth, mHeight };

    // set clip rendering dimensions
    if( clip != NULL )
    {
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }

    // render
    SDL_RenderCopyEx( gRenderer, mTexture, clip, &renderQuad, angle, center, flip );
}

// getters
int LTexture::getWidth()
{
    return mWidth;
}

int LTexture::getHeight()
{
    return mHeight;
}

SDL_Texture* LTexture::getTexture()
{
    return mTexture;
}
