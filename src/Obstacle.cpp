#include "Obstacle.h"

Obstacle::Obstacle(int posX, int posY, int screenWidth, int screenHeight)
{
    failed = false;

    oPosX = posX;
    oPosY = posY;

    this->screenWidth = screenWidth;
    this->screenHeight = screenHeight;
}

void Obstacle::handleEvent( SDL_Event& e )
{

}

bool Obstacle::move( float obsSpeed, Direction obsDir )
{

    if (failed) {
        return obsDir;
    }

    bool changeDir = false;

    switch(obsDir)
    {
        case right:
            oVelX = OBSTACLE_VEL;
            oVelY = 0;
            break;
        case left:
            oVelX = -OBSTACLE_VEL;
            break;
        case up:
            oVelX = 0;
            oVelY = -OBSTACLE_VEL;
            break;
        case down:
            oVelX = 0;
            oVelY = -OBSTACLE_VEL;
            break;
        default:
            oVelX = 0;
            oVelY = 0;
            break;
    }

    // x position
    oPosX += oVelX;

    // check position relative to border
    if( (oPosX < 0) || (oPosX + OBSTACLE_WIDTH > screenWidth) )
    {
        oPosX -= oVelX;

        changeDir = true;
    }

    // y position
    oPosY += oVelY;

    // check position relative to border
    if( ( oPosY < 0 ) || ( oPosY + OBSTACLE_HEIGHT > screenHeight ) )
    {
        oPosY -= oVelY;
    }

    return changeDir;
}

void Obstacle::render( SDL_Renderer* gRenderer, LTexture *gObsTexture )
{
    gObsTexture->render(gRenderer, oPosX, oPosY);
}

int Obstacle::getPosX()
{
    return oPosX; 
}

int Obstacle::getPosY()
{
    return oPosY;
}