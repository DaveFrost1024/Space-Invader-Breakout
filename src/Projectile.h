#ifndef PROJECTILE_H
#define PROJECTILE_H

#include <SDL2/SDL.h>
#include <string>
#include <iostream>

#include "LTexture.h"
#include "common.h"

class Projectile
{
public:
    // dimension
    static const int PROJECTILE_HEIGHT  = 24;
    static const int PROJECTILE_WIDTH = 6;

    // velocity
    static const int PROJECTILE_VEL = 3;

    Projectile( int posX, int posY, int screenWidth, int screenHeight );

    // respond to events
    void handleEvent( SDL_Event& e );

    // move the obstacle
    bool move( SDL_Rect paddle );

    void render( SDL_Renderer* gRenderer );

    // getters
    int getPosX();

    int getPosY();

    SDL_Rect getCollider();

private:
    bool failed;

    // current position
    int prPosX, prPosY;

    // current velocity
    int prVelX, prVelY;

    int screenWidth, screenHeight;

    SDL_Rect collider;

    void shiftColliders();
};

#endif /* PROJECTILE_H */