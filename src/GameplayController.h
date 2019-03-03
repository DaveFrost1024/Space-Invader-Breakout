#ifndef GAMEPLAYCONTROLLER_H
#define GAMEPLAYCONTROLLER_H

#include <SDL2/SDL.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>

#include "Setup.h"
#include "Common.h"
#include "LTexture.h"
#include "WindowController.h"



class GameplayController
{
public:
    static void gameLoop();

    static void startProg();

    static bool updatePhysics();

    static void renderGame();

private:
    static bool quit;

    static bool fail;
    static bool restart;

    static int tps;
    static int skipT;
    static int maxFrameSkip;
    static int updateLoop;
    static double dt;
    static double interpolation;
    static double currentT;

    static double newT;



    static Direction gObsDir;

    static int projCooldown;

    static SDL_Event e;

    static Dot dot;
    static Paddle paddle;

    static std::vector<Obstacle> obsGroup;

    static std::vector<Projectile> projGroup;

    static std::vector<SDL_Rect> rects;
    static std::vector<Type> rectTypes;

};

#endif /* GAMEPLAYCONTROLLER_H */