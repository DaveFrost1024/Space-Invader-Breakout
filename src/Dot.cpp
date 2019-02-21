#include "Dot.h"

const float Dot::DOT_VEL = 5;

Dot::Dot( int x, int y, int screenWidth, int screenHeight )
{
    init = false;

    mPosX = x;
    mPosY = y;

    // set radius
    mCollider.r = DOT_WIDTH / 2;

    //DOT_VEL = 5;
    mVelX = 0;
    mVelY = 0;

    this->screenWidth = screenWidth;
    this->screenHeight = screenHeight;

    // move collider
    shiftColliders();
}

void Dot::handleEvent( SDL_Event& e )
{
    // handle key press
    if( e.type == SDL_KEYDOWN && e.key.repeat == 0 )
    {
        switch( e.key.keysym.sym )
        {
            case SDLK_RETURN: initBounce();  break;
        }
    }

    // handle key release
    /*else if( e.type == SDL_KEYUP && e.key.repeat == 0 )
    {
        switch( e.key.keysym.sym )
        {
            case SDLK_UP: mVelY += DOT_VEL; break;
        }
    }*/
}

int Dot::move( std::vector<SDL_Rect> *square, std::vector<Circle *> *circle )
{

    // move x position
    mPosX += mVelX;
    shiftColliders();

    int collideX = checkCollisions( mCollider, square );

    // check x collision and border
    if( ( mPosX - mCollider.r < 0 ) || ( mPosX + mCollider.r > screenWidth ) ||
        collideX >= 0 /*|| checkCollision( mCollider, circle )*/ )
    {
        // move back
        mPosX -= mVelX;

        // reverse direction
        mVelX = -mVelX;

        shiftColliders();
    }

    // move y position
    mPosY += mVelY;
    shiftColliders();

    int collideY = checkCollisions( mCollider, square );

    // check y collision and border
    if( ( mPosY - mCollider.r < 0 ) ||
        collideY >= 0 /*|| checkCollision( mCollider, circle )*/ )
    {
        // move back
        mPosY -= mVelY;

        // reverse direction
        mVelY = -mVelY;

        shiftColliders();
    }

    // failure
    if ( mPosY + mCollider.r >= screenHeight )
    {
        mVelX = 0;
        mVelY = 0;
        return -2;
    }

    if ( collideY == -1 )
    {
        return collideX;
    }
    else
    {
        return collideY;
    }
}

void Dot::render( SDL_Renderer* gRenderer, LTexture *gDotTexture )
{
    gDotTexture->render( gRenderer, mPosX - mCollider.r, mPosY - mCollider.r );
}

void Dot::initBounce()
{
    if ( !init )
    {
        mVelX = Dot::DOT_VEL * ((float)(rand() % 200 - 100) / 100);
        //std::cout << mVelX << std::endl;

        // Pythagoreas formula
        mVelY = -( sqrt( pow(Dot::DOT_VEL, 2) - pow(mVelX, 2) ) );
        //std::cout << "Y: " << mVelY << std::endl;

        init = true;
    }
}

bool Dot::getInit()
{
    return init;
}

float Dot::getPosX()
{
    return mPosX;
}

float Dot::getPosY()
{
    return mPosY;
}

float Dot::getVelX()
{
    return mVelX;
}

float Dot::getVelY()
{
    return mVelY;
}

Circle& Dot::getCollider()
{
    return mCollider;
}

void Dot::setInit( bool init )
{
    this->init = init;
}

void Dot::setPos( float posX, float posY )
{
    mPosX = posX;
    mPosY = posY;
}

void Dot::setVel( float mVelX, float mVelY )
{
    this->mVelX = mVelX;
    this->mVelY = mVelY;
}

void Dot::shiftColliders()
{
    // align collider
    mCollider.x = mPosX;
    mCollider.y = mPosY;
} 