#define CATCH_CONFIG_MAIN

//#include <catch2/catch.hpp>
#include "../include/catch.hpp"

#include "../src/Common.h"
#include "../src/Common.cpp"

TEST_CASE( "Common distancesquared", "[distancesquared]" )
{
    REQUIRE( distanceSquared( 1, 1, 1, 1 ) == 0 );
    REQUIRE( distanceSquared( 1, 1, 2, 2 ) == 2 );
    REQUIRE( distanceSquared( -1, -1, -2, -2 ) == 2 );
    REQUIRE( distanceSquared( 3, -2, -5, 7 ) == 145 );
}

TEST_CASE( "Common single collision", "[checkcollision]" )
{
    Circle cCollide;
    cCollide.x = 100;
    cCollide.y = 100;
    cCollide.r = 10;

    SDL_Rect rCollide;
    rCollide.x = 100;
    rCollide.y = 100;
    rCollide.w = 10;
    rCollide.h = 10;

    REQUIRE( checkCollision( cCollide, rCollide ) == true );
}
