#ifndef DOT_H
#define DOT_H

#include <SDL2/SDL.h>
#include <string>
#include <iostream>

#include "LTexture.h"
#include "common.h"

class Dot
{
public:
    // dimensions
    static const int DOT_WIDTH = 20;
    static const int DOT_HEIGHT = 20;

    // velocity
    static const float DOT_VEL;

    Dot( int x, int y, int screenWidth, int screenHeight );

    // takes key presses and adjusts the dot's velocity
    void handleEvent( SDL_Event& e );

    // moves dot and check collision
    int move( std::vector<SDL_Rect> *square, std::vector<Circle *> *circle = nullptr );

    void render( SDL_Renderer* gRenderer, LTexture *gProjTexture );

    void initBounce();

    // getter
    bool getInit();

    float getPosX();

    float getPosY();

    float getVelX();

    float getVelY();

    Circle& getCollider();

    // setter
    void setInit( bool init );

    void setPos(float posX, float posY);

    void setVel(float mVelX, float mVelY);

private:
    // started
    bool init;

    // position
    float mPosX, mPosY;

    // velocity
    float mVelX, mVelY;
    
    Circle mCollider;

    int screenWidth, screenHeight;

    // move the collider in sync
    void shiftColliders();
};

#endif /* DOT_H */