#ifndef SETUP_H
#define SETUP_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <iostream>
#include <vector>

#include "Common.h"
#include "LTexture.h"
#include "Paddle.h"
#include "Dot.h"
#include "Obstacle.h"
#include "Projectile.h"
#include "WindowController.h"

// starts up SDL and creates window
bool initWindow();

bool initRenderer();

// loads images
bool loadMedia( TTF_Font* gFont );

// sets up the game
void startProg( Dot *dot, Paddle *paddle, std::vector<Obstacle> *obsGroup,
    std::vector<SDL_Rect> *rects, std::vector<Type> *rectTypes );

// generates all the space invaders
std::vector<Obstacle> generateObstacle( int row, int column);

// frees images and shuts down SDL
void close( TTF_Font* gFont );

#endif /* SETUP_H */