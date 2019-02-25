#include "Gameplay.h"

void gameLoop() {
    SDL_Renderer* gRenderer = WindowController::getSdlRenderer();

    LTexture* gDotTexture = WindowController::getTexture( "gDotTexture" );
    LTexture* gObsTexture = WindowController::getTexture( "gObsTexture" );
    LTexture* gTextTexture = WindowController::getTexture( "gTextTexture" );

    //set the seed for RNG
    srand(time(NULL));

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
    obsGroup.reserve( OBSTACLE_ROW * OBSTACLE_COLUMN );

    std::vector<Projectile> projGroup;
    // Limits the amount of projectiles that can be on screen
    projGroup.reserve( PROJECTILE_LIMIT );

    // vector containing all collider hitbox and their type
    std::vector<SDL_Rect> rects;
    std::vector<Type> rectTypes;
    rects.reserve( OBSTACLE_ROW * OBSTACLE_COLUMN + 6 );
    rectTypes.reserve( OBSTACLE_ROW * OBSTACLE_COLUMN + 6 );

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
            dot.render( gRenderer, gDotTexture );

            // render obstacles
            for (int i = 0; i < obsGroup.size(); i++)
            {
                obsGroup[i].render( gRenderer, gObsTexture );
            }

            // render projectiles
            for (int i = 0; i < projGroup.size(); i++)
            {
                projGroup[i].render( gRenderer );
            }

            if ( !dot.getInit() )
            {
                gTextTexture->render( gRenderer, ( SCREEN_WIDTH - gTextTexture->getWidth() ) * 5 / 8,
                    ( SCREEN_HEIGHT - gTextTexture->getHeight() )*2 / 3 );
            }

            // update screen
            SDL_RenderPresent( gRenderer );
        } else {
            paddle.setFailed( true );
        }

    }
}