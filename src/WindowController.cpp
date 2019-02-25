#include "WindowController.h"

SDL_Window* WindowController::gWindow = NULL;
SDL_Renderer* WindowController::gRenderer = NULL;

std::map<std::string, LTexture> WindowController::gTextures = {};

SDL_Window* WindowController::getSdlWindow()
{
    return gWindow;
}

SDL_Renderer* WindowController::getSdlRenderer()
{
    return gRenderer;
}

void WindowController::setSdlWindow( SDL_Window* window )
{
    gWindow = window;
}

void WindowController::setSdlRenderer( SDL_Renderer* renderer )
{
    gRenderer = renderer;
}

LTexture* WindowController::getTexture( std::string key )
{
    return &gTextures.at( key );
}

void WindowController::insertTexture( std::string key, LTexture value )
{
    gTextures.insert( std::pair<std::string, LTexture>( key, value ) );
}
