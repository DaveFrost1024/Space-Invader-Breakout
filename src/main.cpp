#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>

#include "Setup.h"
#include "Common.h"
#include "LTexture.h"
#include "GameplayController.h"
#include "WindowController.h"


// TODO:
// > New screen when no obstacle



int main( int argc, char* args[] )
{

    // track initiation status
    bool windowSuccess;
    bool rendererSuccess;

    // initialize window and renderer
    windowSuccess = initWindow();
    rendererSuccess = initRenderer();

    // textures and fonts
    TTF_Font* gFont = NULL;

    if( windowSuccess == false || rendererSuccess == false )
    {
        printf( "Failed to initialize!\n" );
    }
    else
    {
        // load media
        if( !loadMedia( gFont ) )
        {
            printf( "Failed to load media!\n" );
        }
        else
        {   
            // begin the loop
            GameplayController::gameLoop();
        }
    }

    // free resources and close SDL
    close( gFont );

    return 0;
}