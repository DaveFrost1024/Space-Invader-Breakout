#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <math.h>

#include "common.h"
#include "LTexture.h"
#include "Paddle.h"
#include "Dot.h"
#include "Obstacle.h"
#include "Projectile.h"

// TODO:
// > New screen when no obstacle

// screen dimension
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

const int OBSTACLE_ROW = 3;
const int OBSTACLE_COLUMN = 7;

const int PROJECTILE_LIMIT = 5;
const int PROJ_MIN_COOLDOWN = 15;
const int PROJ_MAX_COOLDOWN = 180;

// starts up SDL and creates window
bool init();

// loads images
bool loadMedia();

// frees images and shuts down SDL
void close();

// handling global events
void handleEvent( SDL_Event& e, bool fail );

void startProg( Dot *dot, Paddle *paddle, std::vector<Obstacle> *obsGroup,
    std::vector<SDL_Rect> *rects, std::vector<Type> *rectTypes );

std::vector<Obstacle> generateObstacle( int row, int column);

// rendering window
SDL_Window* gWindow = NULL;

SDL_Renderer* gRenderer = NULL;

// texture, from texture.h
LTexture gDotTexture;

LTexture gObsTexture;

LTexture gTextTexture;

TTF_Font *gFont;



bool init()
{
    bool success = true;

    // initialize SDL
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
        success = false;
    }
    else
    {
        // set texture filtering to linear
        if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
        {
            printf( "Warning: Linear texture filtering not enabled!" );
        }

        // create window
        gWindow = SDL_CreateWindow( "SDL Project 1", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
            SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
        if( gWindow == NULL )
        {
            printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
            success = false;
        }
        else
        {
            //Create vsynced renderer
            gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
            if( gRenderer == NULL )
            {
                printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
                success = false;
            }
            else
            {
                // initialize renderer color
                SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

                // initialize PNG loading
                int imgFlags = IMG_INIT_PNG;
                if( !( IMG_Init( imgFlags ) & imgFlags ) )
                {
                    printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
                    success = false;
                }

                // initialize SDL_ttf
                if( TTF_Init() == -1 )
                {
                    printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
                    success = false;
                }
            }
        }
    }

    return success;
}

bool loadMedia()
{
    bool success = true;

    // load texture
    if( !gDotTexture.loadFromFile( gRenderer, "../media/Ball.png", 20, 20 ) )
    {
        printf( "Failed to load dot texture!\n" );
        success = false;
    }

    if ( !gObsTexture.loadFromFile( gRenderer, "../media/space-invaders-sprite.png", 50, 50 ) )
    {
        printf( "Failed to load invader texture\n" );
        success = false;
    }

    // load helvatica font
    gFont = TTF_OpenFont( "../media/Helvetica.ttf", 28 );
    if( gFont == NULL )
    {
        printf( "Failed to load helvetica font! SDL_ttf Error: %s\n", TTF_GetError() );
        success = false;
    }
    else
    {
        // load text texture
        SDL_Color textColor = { 255, 255, 255 };
        if( !gTextTexture.loadFromRenderedText( gRenderer, gFont, "Enter", textColor ) )
        {
            printf( "Failed to render text texture!\n" );
        }
    }

    return success;
}

void close()
{
    // free loaded images
    gDotTexture.free();
    gObsTexture.free();
    gTextTexture.free();

    // destroy window    
    SDL_DestroyRenderer( gRenderer );
    SDL_DestroyWindow( gWindow );
    gWindow = NULL;
    gRenderer = NULL;

    // quit SDL subsystems
    IMG_Quit();
    SDL_Quit();
}

void handleEvent( SDL_Event& e, bool fail )
{
    // No event to handle for now
}

void startProg( Dot *dot, Paddle *paddle, std::vector<Obstacle> *obsGroup,
    std::vector<SDL_Rect> *rects, std::vector<Type> *rectTypes )
{
    dot->setInit( false );
    dot->setPos( SCREEN_WIDTH / 2, SCREEN_HEIGHT * 3 / 4 );
    dot->setVel( 0, 0 );
    paddle->setFailed( false );
    paddle->setPos( (SCREEN_WIDTH / 2) - (Paddle::PADDLE_WIDTH / 2), SCREEN_HEIGHT * 7 / 8 );
    paddle->setVel( 0, 0 );

    obsGroup->clear();
    rects->clear();
    rectTypes->clear();

    std::vector<Obstacle> tempObsGroup = generateObstacle( OBSTACLE_ROW, OBSTACLE_COLUMN );
    for(int i = 0; i < tempObsGroup.size(); i++)
    {
        obsGroup->push_back(tempObsGroup[i]);
    }

    SDL_Rect pRect;
    pRect.w = Paddle::PADDLE_WIDTH;
    pRect.h = Paddle::PADDLE_HEIGHT;
    pRect.x = paddle->getPosX();
    pRect.y = paddle->getPosY();

    rects->push_back(pRect);
    rectTypes->push_back(Type::paddle);

    for (int i = 0; i < obsGroup->size(); i++)
    {
        SDL_Rect oRect;
        oRect.w = Obstacle::OBSTACLE_WIDTH;
        oRect.h = Obstacle::OBSTACLE_HEIGHT;
        oRect.x = obsGroup->at(i).getPosX();
        oRect.y = obsGroup->at(i).getPosY();

        rects->push_back(oRect);
        rectTypes->push_back(Type::obstacle);
    }
}

std::vector<Obstacle> generateObstacle( int row, int column )
{
    std::vector<Obstacle> obsGroup;

    float paddingTop = SCREEN_HEIGHT / 10;
    float paddingSide = SCREEN_WIDTH / 6;

    float spacingX = ( ( SCREEN_WIDTH - (paddingSide * 2) - (Obstacle::OBSTACLE_WIDTH * column) ) / (column+1) );
    float spacingY = spacingX;

    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < column; j++)
        {
            Obstacle obs( paddingSide + spacingX + ( (spacingX + Obstacle::OBSTACLE_WIDTH) * j ),
                paddingTop + spacingY + ( (spacingY + Obstacle::OBSTACLE_HEIGHT) * i ), SCREEN_WIDTH, SCREEN_HEIGHT );
            obsGroup.push_back(obs);
        }
    }

    return obsGroup;
}



int main( int argc, char* args[] )
{
    //set the seed for RNG
    srand(time(NULL));

    // start up SDL and create window
    if( !init() )
    {
        printf( "Failed to initialize!\n" );
    }
    else
    {
        // load media
        if( !loadMedia() )
        {
            printf( "Failed to load media!\n" );
        }
        else
        {   
            // program quit state
            bool quit = false;

            // session state
            bool fail = false;
            bool restart = false;

            // obstacle variable
            bool changeDir = false;
            float gObsSpeed = 3;

            Direction gObsDir;
            // make initial obstacle direction random
            rand() % 2 ? gObsDir = right : gObsDir = left;

            // dot variable
            int collideState = -1;

            // projectile variable
            int projCooldown = rand() % PROJ_MAX_COOLDOWN + 15;

            SDL_Event e;

            // instantiate dot and paddle
            Dot dot( SCREEN_WIDTH / 2, SCREEN_HEIGHT * 3 / 4, SCREEN_WIDTH, SCREEN_HEIGHT );
            Paddle paddle( (SCREEN_WIDTH / 2) - (Paddle::PADDLE_WIDTH / 2), SCREEN_HEIGHT * 7 / 8, SCREEN_WIDTH, SCREEN_HEIGHT );

            // instantiate vector holding all obstacles
            std::vector<Obstacle> obsGroup;

            std::vector<Projectile> projGroup;

            // vector containing all collider hitbox and their type
            std::vector<SDL_Rect> rects;
            std::vector<Type> rectTypes;

            startProg(&dot, &paddle, &obsGroup, &rects, &rectTypes);

            // main loop
            while( !quit )
            {
                while( SDL_PollEvent( &e ) != 0 )
                {
                    // quit event registered, via closing window etc
                    if( e.type == SDL_QUIT )
                    {
                        quit = true;
                    }

                    //handleEvent( e );

                    dot.handleEvent( e );

                    paddle.handleEvent ( e );

                    if ( fail )
                    {
                        if( e.type == SDL_KEYDOWN && e.key.repeat == 0 )
                        {
                            // wait for user to restart
                            switch( e.key.keysym.sym )
                            {
                                case SDLK_RETURN: restart = true; break;
                            }
                        }
                    }
                }



                if ( restart )
                {
                    std::cout << "restarting!" << std::endl;

                    startProg(&dot, &paddle, &obsGroup, &rects, &rectTypes);
                    projGroup.clear();

                    fail = false;
                    restart = false;

                    // make initial obstacle direction random
                    rand() % 2 ? gObsDir = right : gObsDir = left;
                }



                if ( !fail ) {
                    // move and check collision
                    collideState = dot.move( &rects );

                    // collided with bottom
                    if ( collideState == -2 )
                    {
                        fail = true;
                    }
                    // collided with paddle
                    else if ( collideState == 0 )
                    {
                        // new angle in degree and radian
                        float velDeg = 0;
                        float velRad = 0;

                        // position of dot relative to paddle center
                        float collidePos = dot.getPosX() - ( paddle.getPosX() + (Paddle::PADDLE_WIDTH / 2) );

                        // current velocity
                        float collideVel = sqrt( pow(dot.getVelX(), 2) + pow(dot.getVelY(), 2) );

                        // upper limit of angle
                        if ( collidePos <= -(Paddle::PADDLE_WIDTH / 2) - (Dot::DOT_WIDTH / 2) )
                        {
                            velDeg = 150;
                        }
                        // lower limit of angle
                        else if ( collidePos >= (Paddle::PADDLE_WIDTH / 2) + (Dot::DOT_WIDTH / 2) )
                        {
                            velDeg = 30;
                        }
                        else
                        {
                            // calculate angle
                            if ( collidePos >= 0 )
                            {
                                velDeg = 30 + ( 1 - ( collidePos / ((Paddle::PADDLE_WIDTH / 2) + (Dot::DOT_WIDTH / 2)) ) ) * 60;
                            }
                            else if ( collidePos < 0 )
                            {
                                velDeg = 150 - ( 1 - ( -(collidePos) / ((Paddle::PADDLE_WIDTH / 2) + (Dot::DOT_WIDTH / 2)) ) ) * 60;
                            }
                        }
                        // convert to radian
                        velRad = velDeg * M_PI / 180.0;

                        // give dot new velocity
                        dot.setVel ( cos(velRad) * collideVel, -(sin(velRad) * collideVel) );
                    }
                    // collided with obstacle
                    else if ( collideState > 0 && rectTypes[collideState] == Type::obstacle )
                    {
                        obsGroup.erase( obsGroup.begin() + (collideState-1) );

                        rectTypes.erase(rectTypes.begin()+collideState);
                        rects.erase(rects.begin()+collideState);
                    }



                    paddle.move();

                    changeDir = false;
                    if ( dot.getInit() )
                    {
                        for (int i = 0; i < obsGroup.size(); i++)
                        {
                            
                            if ( obsGroup[i].move( gObsSpeed, gObsDir ) )
                            {
                                changeDir = true;
                            }

                            rects[i+1].x = obsGroup[i].getPosX();
                            rects[i+1].y = obsGroup[i].getPosY();
                        }
                    }

                    if (changeDir)
                    {
                        switch(gObsDir)
                        {
                            case left:
                                gObsDir = Direction::right;
                                break;
                            case right:
                                gObsDir = Direction::left;
                                break;
                        }
                    }

                    rects[0].x = paddle.getPosX();
                    rects[0].y = paddle.getPosY();

                    for (int i = 0; i < projGroup.size(); i++)
                    {
                        if ( projGroup[i].move( rects[0] ) )
                        {
                            fail = true;
                        }

                        float tempPosY = projGroup[i].getPosY();
                        if ( tempPosY > SCREEN_HEIGHT || tempPosY + Projectile::PROJECTILE_HEIGHT < 0 )
                        {
                            projGroup.erase(projGroup.begin()+i);
                        }
                    }

                    // Instantiate projectiles
                    if ( projCooldown <= 0 )
                    {
                        if ( obsGroup.size() > 0 && projGroup.size() < PROJECTILE_LIMIT)
                        {
                            int targetObs = rand() % obsGroup.size();
                            Projectile proj
                            (
                                obsGroup[targetObs].getPosX() + (Obstacle::OBSTACLE_WIDTH / 2) - (Projectile::PROJECTILE_WIDTH / 2),
                                obsGroup[targetObs].getPosY() + (Obstacle::OBSTACLE_HEIGHT / 2), SCREEN_WIDTH, SCREEN_HEIGHT
                            );
                            projGroup.push_back(proj);

                            projCooldown = rand() % PROJ_MAX_COOLDOWN + PROJ_MIN_COOLDOWN;
                        }
                    }
                    else if ( dot.getInit() )
                    {
                        projCooldown--;
                    }

                    // clear screen
                    SDL_SetRenderDrawColor( gRenderer, 0x00, 0x00, 0x00, 0xFF );
                    SDL_RenderClear( gRenderer );

                    // render paddle
                    SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
                    SDL_RenderDrawRect( gRenderer, &rects[0] );
                    
                    // render dot
                    dot.render( gRenderer, &gDotTexture );

                    // render obstacles
                    for (int i = 0; i < obsGroup.size(); i++)
                    {
                        obsGroup[i].render( gRenderer, &gObsTexture );
                    }

                    // render projectiles
                    for (int i = 0; i < projGroup.size(); i++)
                    {
                        projGroup[i].render( gRenderer );
                    }

                    if ( !dot.getInit() )
                    {
                        gTextTexture.render( gRenderer, ( SCREEN_WIDTH - gTextTexture.getWidth() ) * 5 / 8,
                            ( SCREEN_HEIGHT - gTextTexture.getHeight() )*2 / 3 );
                    }

                    // update screen
                    SDL_RenderPresent( gRenderer );
                } else {
                    paddle.setFailed( true );
                }

            }
        }
    }

    // free resources and close SDL
    close();

    return 0;
}