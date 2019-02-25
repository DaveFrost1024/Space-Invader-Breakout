#define CATCH_CONFIG_MAIN

//#include <catch2/catch.hpp>
#include "../include/catch.hpp"

#include "../src/Common.h"
#include "../src/Common.cpp"

TEST_CASE( "Common functions", "[distancesquared]" )
{
    REQUIRE( distanceSquared( 1, 1, 1, 1 ) == 0 );
    REQUIRE( distanceSquared( 1, 1, 2, 2 ) == 2 );
    REQUIRE( distanceSquared( -1, -1, -2, -2 ) == 2 );
    REQUIRE( distanceSquared( 3, -2, -5, 7 ) == 145 );
}
