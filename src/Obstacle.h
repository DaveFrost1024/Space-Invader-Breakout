#ifndef OBSTACLE_H
#define OBSTACLE_H

#include <SDL2/SDL.h>
#include <string>
#include <iostream>

#include "LTexture.h"
#include "Common.h"

// obstacles that are in your way
class Obstacle
{
public:
    // dimension
    static const int OBSTACLE_HEIGHT  = 50;
    static const int OBSTACLE_WIDTH = 50;

    // velocity
    static const int OBSTACLE_VEL = 1;

    Obstacle( int posX, int posY, int screenWidth, int screenHeight );

    // respond to events
    void handleEvent( SDL_Event& e );

    // move the obstacle
    bool move( float obsSpeed, Direction obsDir );

    void render( SDL_Renderer* gRenderer, LTexture *gObsTexture );
    void render( SDL_Renderer* gRenderer, LTexture *gObsTexture, double interpolation );

    // getters
    int getPosX();

    int getPosY();

private:
    bool failed;

    // current position
    int oPosX, oPosY;

    // current velocity
    int oVelX, oVelY;

    // need this to make sure obstacle don't go out of bounds
    int screenWidth, screenHeight;

    void shiftColliders();
};

#endif /* OBSTACLE_H */