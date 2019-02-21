#include "Paddle.h"

Paddle::Paddle( int x, int y, int screenWidth, int screenHeight ) {
    failed = false;

    pPosX = x;
    pPosY = y;

    pVelX = 0;
    pVelY = 0;

    this->screenWidth = screenWidth;
    this->screenHeight = screenHeight;
}

void Paddle::handleEvent( SDL_Event& e )
{
    if ( failed ) {
        return;
    }

    if( e.type == SDL_KEYDOWN && e.key.repeat == 0 )
    {
        // change velocity accordingly
        switch( e.key.keysym.sym )
        {
            case SDLK_LEFT: pVelX -= PADDLE_VEL; break;
            case SDLK_RIGHT: pVelX += PADDLE_VEL; break;
        }
    }

    // handles key release
    else if( e.type == SDL_KEYUP && e.key.repeat == 0 )
    {
        // change velocity accordingly
        switch( e.key.keysym.sym )
        {
            case SDLK_LEFT: pVelX = 0; break;
            case SDLK_RIGHT: pVelX = 0; break;
        }
    }
}

void Paddle::move() {
    if ( failed ) {
        return;
    }

    // x position
    pPosX += pVelX;

    // check position relative to border
    if( ( pPosX < 0 ) || ( pPosX + PADDLE_WIDTH > screenWidth ) )
    {
        pPosX -= pVelX;
    }

    // y position
    pPosY += pVelY;

    // check position relative to border
    if( ( pPosY < 0 ) || ( pPosY + PADDLE_HEIGHT > screenHeight ) )
    {
        pPosY -= pVelY;
    }
}

int Paddle::getPosX() {
    return pPosX;
}

int Paddle::getPosY() {
    return pPosY;
}

void Paddle::setFailed( bool failed )
{
    this->failed = failed;
}

void Paddle::setPos( int posX, int posY )
{
    pPosX = posX;
    pPosY = posY;
}

void Paddle::setVel( int velX, int velY )
{
    pVelX = velX;
    pVelY = velY;
}
