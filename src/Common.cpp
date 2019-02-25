#include "Common.h"

bool checkCollision( Circle& a, std::vector<Circle>& b )
{
    // calculate total radius squared
    for (int i = 0; i < b.size(); i++)
    {
        int totalRadiusSquared = a.r + b[i].r;
        totalRadiusSquared = totalRadiusSquared * totalRadiusSquared;

        // check collision via distance between circles center
        if( distanceSquared( a.x, a.y, b[i].x, b[i].y ) < ( totalRadiusSquared ) )
        {
            return true;
        }
    }

    return false;
}

int checkCollisions( Circle& a, std::vector<SDL_Rect> *b )
{
    for(int i = 0; i < b->size(); i++)
    {
        // check individual rectangle for collision
        if ( checkCollision( a, b->at(i) ))
        {
            return i;
        }

    }

    return -1;
}

bool checkCollision( Circle& a, SDL_Rect b )
{
    // find closest point on collision box
    int cX, cY;

    // find x
    if( a.x < b.x )
    {
        cX = b.x;
    }
    else if( a.x > b.x + b.w )
    {
        cX = b.x + b.w;
    }
    else
    {
        cX = a.x;
    }


    // find y
    if( a.y < b.y )
    {
        cY = b.y;
    }
    else if( a.y > b.y + b.h )
    {
        cY = b.y + b.h;
    }
    else
    {
        cY = a.y;
    }

    // closest point is inside circle
    if( distanceSquared( a.x, a.y, cX, cY ) < a.r * a.r )
    {
        return true;
    }

    return false;
}

bool checkCollision( SDL_Rect a, SDL_Rect b )
{
    if( a.y + a.h <= b.y )
    {
        return false;
    }

    if( a.y >= b.y + b.h )
    {
        return false;
    }

    if( a.x + a.w <= b.x )
    {
        return false;
    }

    if( a.x >= b.x + b.w )
    {
        return false;
    }

    return true;
}

double distanceSquared( int x1, int y1, int x2, int y2 )
{
    int deltaX = x2 - x1;
    int deltaY = y2 - y1;
    return deltaX*deltaX + deltaY*deltaY;
}