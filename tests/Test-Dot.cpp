
//#include <catch2/catch.hpp>
#include "../include/catch.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "../src/Dot.h"
#include "../src/Dot.cpp"
#include "../src/LTexture.h"
#include "../src/LTexture.cpp"

TEST_CASE( "Dot constructor", "[Dot::Dot]" )
{
    Dot testd1 ( 10, 20, 100, 100);

    REQUIRE( testd1.getInit() == false );
    REQUIRE( testd1.getPosX() == 10 );
    REQUIRE( testd1.getPosY() == 20 );
    REQUIRE( testd1.getVelX() == 0 );
    REQUIRE( testd1.getVelY() == 0 );

    Circle testdc1 = testd1.getCollider();
    REQUIRE( testdc1.r == 10 );
}