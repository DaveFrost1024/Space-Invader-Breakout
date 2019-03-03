#include "Projectile.h"

Projectile::Projectile( int posX, int posY, int screenWidth, int screenHeight )
{
    failed = false;

    prPosX = posX;
    prPosY = posY;

    prVelY = PROJECTILE_VEL;
    prVelX = 0;

    this->screenWidth = screenWidth;
    this->screenHeight = screenHeight;

    collider.x = posX;
    collider.y = posY;
    collider.w = PROJECTILE_WIDTH;
    collider.h = PROJECTILE_HEIGHT;
}

void Projectile::handleEvent( SDL_Event& e )
{

}

bool Projectile::move( SDL_Rect paddle )
{
    if (failed) {
        return false;
    }

    bool hit = false;

    // x position
    prPosX += prVelX;

    // y position
    prPosY += prVelY;

    shiftColliders();

    hit = checkCollision( collider, paddle );

    return hit;
}

void Projectile::render( SDL_Renderer* gRenderer )
{
    //gProjTexture->render(gRenderer, prPosX, prPosY);

    SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
    SDL_RenderFillRect( gRenderer, &collider );

}

void Projectile::render( SDL_Renderer* gRenderer, double interpolation )
{
    SDL_Rect temp = collider;
    temp.x = temp.x + (prVelX * interpolation);
    temp.y = temp.y + (prVelY * interpolation);
    SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
    SDL_RenderFillRect( gRenderer, &temp );

}

void Projectile::shiftColliders()
{
    // align collider
    collider.x = prPosX;
    collider.y = prPosY;
} 

int Projectile::getPosX()
{
    return prPosX; 
}

int Projectile::getPosY()
{
    return prPosY;
}

SDL_Rect Projectile::getCollider()
{
    return collider;
}
