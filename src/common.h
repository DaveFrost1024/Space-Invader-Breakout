#ifndef COMMON_H
#define COMMON_H

#include <SDL2/SDL.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>


enum Type
{
    paddle,
    obstacle
};

enum Direction
{
    left,
    right,
    up,
    down
};

// struct for circle collider
struct Circle
{
    int x, y;
    int r;
};

// circle/circle collision
bool checkCollision( Circle& a, std::vector<Circle *> b );

// all circle/box collision
int checkCollisions( Circle& a, std::vector<SDL_Rect> *b );

// individual circle/box collision
bool checkCollision( Circle &a, SDL_Rect b );

// box/box collision
bool checkCollision( SDL_Rect a, SDL_Rect b );

double distanceSquared( int x1, int y1, int x2, int y2 );

#endif /* COMMON_H */