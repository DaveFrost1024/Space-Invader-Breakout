#ifndef WINDOWCONTROLLER_H
#define WINDOWCONTROLLER_H

#include <SDL2/SDL.h>
#include <map>

#include "LTexture.h"

class WindowController
{
public:
    static SDL_Window* getSdlWindow();
    static SDL_Renderer* getSdlRenderer();
    static LTexture* getTexture( std::string key );

    static void setSdlWindow( SDL_Window* gWindow );
    static void setSdlRenderer( SDL_Renderer* gRenderer );
    static void insertTexture( std::string key, LTexture value );

private:
    static SDL_Window* gWindow;
    static SDL_Renderer* gRenderer;

    static std::map<std::string, LTexture> gTextures;
};

#endif /* WINDOWCONTROLLER_H */