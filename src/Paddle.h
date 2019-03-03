#ifndef PADDLE_H
#define PADDLE_H

#include <SDL2/SDL.h>
#include <iostream>

// paddle that bounces the dot
class Paddle
{
public:
    // dimension
    static const int PADDLE_HEIGHT  = 20;
    static const int PADDLE_WIDTH = 120;

    // velocity
    static const int PADDLE_VEL = 5;

    Paddle( int x, int y, int screenWidth, int screenHeight );

    // respond to events
    void handleEvent( SDL_Event& e );

    // move the paddle
    void move();

    // getters
    int getPosX();

    int getPosY();

    int getVelX();

    // setters
    void setFailed( bool failed );

    void setPos( int posX, int posY );

    void setVel( int velX, int velY );

private:
    bool failed;

    // current position
    int pPosX, pPosY;

    // current velocity
    int pVelX, pVelY;

    // need this to make sure paddle don't go out of bounds
    int screenWidth, screenHeight;

    void shiftColliders();
};

#endif /* PADDLE_H */