#include "Setup.h"

SDL_Window* initWindow()
{
    SDL_Window* gWindow;

    // initialize SDL
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
    }
    else
    {
        // set texture filtering to linear
        if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
        {
            printf( "Warning: Linear texture filtering not enabled!" );
        }

        // create window
        gWindow = SDL_CreateWindow( "Space Invader Breakout", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
            SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
        if( gWindow == NULL )
        {
            printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
        }
        else
        {
            return gWindow;
        }
    }

    return NULL;
}

SDL_Renderer* initRenderer( SDL_Window* gWindow )
{
    SDL_Renderer* gRenderer;

    //Create vsynced renderer
    gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
    if( gRenderer == NULL )
    {
        printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
    }
    else
    {
        // initialize renderer color
        SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

        // initialize PNG loading
        int imgFlags = IMG_INIT_PNG;
        if( !( IMG_Init( imgFlags ) & imgFlags ) )
        {
            printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
        }

        // initialize SDL_ttf
        if( TTF_Init() == -1 )
        {
            printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
        }

        return gRenderer;
    }

    return NULL;
}

bool loadMedia( SDL_Renderer* gRenderer, LTexture* gDotTexture, LTexture* gObsTexture, LTexture* gTextTexture, TTF_Font* gFont )
{
    bool success = true;

    // load texture
    if( !gDotTexture->loadFromFile( gRenderer, "../media/Ball.png", 20, 20 ) )
    {
        printf( "Failed to load dot texture!\n" );
        success = false;
    }

    if ( !gObsTexture->loadFromFile( gRenderer, "../media/space-invaders-sprite.png", 50, 50 ) )
    {
        printf( "Failed to load invader texture\n" );
        success = false;
    }

    // load helvatica font
    gFont = TTF_OpenFont( "../media/Helvetica.ttf", 28 );
    if( gFont == NULL )
    {
        printf( "Failed to load helvetica font! SDL_ttf Error: %s\n", TTF_GetError() );
        success = false;
    }
    else
    {
        // load text texture
        SDL_Color textColor = { 255, 255, 255 };
        if( !gTextTexture->loadFromRenderedText( gRenderer, gFont, "Enter", textColor ) )
        {
            printf( "Failed to render text texture!\n" );
        }
    }

    return success;
}

void close( SDL_Window* gWindow, SDL_Renderer* gRenderer, LTexture gDotTexture, LTexture gObsTexture, LTexture gTextTexture, TTF_Font *gFont )
{
    // free loaded images
    gDotTexture.free();
    gObsTexture.free();
    gTextTexture.free();

    TTF_CloseFont( gFont );
    gFont = NULL;

    // destroy window    
    SDL_DestroyRenderer( gRenderer );
    SDL_DestroyWindow( gWindow );
    gWindow = NULL;
    gRenderer = NULL;

    // quit SDL subsystems
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}