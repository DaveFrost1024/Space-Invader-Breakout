#ifndef SETUP_H
#define SETUP_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <iostream>
#include <vector>

#include "common.h"
#include "LTexture.h"

// starts up SDL and creates window
SDL_Window* initWindow();

SDL_Renderer* initRenderer( SDL_Window* gWindow );

// loads images
bool loadMedia( SDL_Renderer* gRenderer, LTexture* gDotTexture, LTexture* gObsTexture, LTexture* gTextTexture, TTF_Font* gFont );

// frees images and shuts down SDL
void close( SDL_Window* gWindow, SDL_Renderer* gRenderer, LTexture gDotTexture, LTexture gObsTexture, LTexture gTextTexture, TTF_Font* gFont );

#endif /* SETUP_H */