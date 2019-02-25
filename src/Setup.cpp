#include "Setup.h"

bool initWindow()
{
    SDL_Window* gWindow;

    // initialize SDL
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
    }
    else
    {
        // set texture filtering to linear
        if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
        {
            printf( "Warning: Linear texture filtering not enabled!" );
        }

        // create window
        gWindow = SDL_CreateWindow( "Space Invader Breakout", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
            SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
        if( gWindow == NULL )
        {
            printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
        }
        else
        {
            WindowController::setSdlWindow( gWindow );

            return true;
        }
    }

    return false;
}

bool initRenderer()
{
    SDL_Window* gWindow = WindowController::getSdlWindow();

    SDL_Renderer* gRenderer;

    //Create vsynced renderer
    gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
    if( gRenderer == NULL )
    {
        printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
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
        }

        // initialize SDL_ttf
        if( TTF_Init() == -1 )
        {
            printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
        }

        WindowController::setSdlRenderer( gRenderer );

        return true;
    }

    return false;
}

bool loadMedia( TTF_Font* gFont )
{
    bool success = true;

    SDL_Renderer* gRenderer = WindowController::getSdlRenderer();

    LTexture dotT;
    LTexture obsT;
    LTexture textT;
    WindowController::insertTexture( "gDotTexture" , dotT );
    WindowController::insertTexture( "gObsTexture" , obsT );
    WindowController::insertTexture( "gTextTexture" , textT );

    LTexture* gDotTexture = WindowController::getTexture( "gDotTexture" );

    LTexture* gObsTexture = WindowController::getTexture( "gObsTexture" );

    LTexture* gTextTexture = WindowController::getTexture( "gTextTexture" );

    // load texture
    if( !gDotTexture->loadFromFile( gRenderer, "../media/Ball.png", 20, 20 ) )
    {
        printf( "Failed to load dot texture!\n" );
        success = false;
    }

    if ( !gObsTexture->loadFromFile( gRenderer, "../media/space-invaders-sprite.png", 50, 50 ) )
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
        if( !gTextTexture->loadFromRenderedText( gRenderer, gFont, "Enter", textColor ) )
        {
            printf( "Failed to render text texture!\n" );
        }
    }

    return success;
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
    obsGroup.reserve( row * column );

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

void close( TTF_Font *gFont )
{
    SDL_Window* gWindow = WindowController::getSdlWindow();
    SDL_Renderer* gRenderer = WindowController::getSdlRenderer();

    LTexture* gDotTexture = WindowController::getTexture( "gDotTexture" );
    LTexture* gObsTexture = WindowController::getTexture( "gObsTexture" );
    LTexture* gTextTexture = WindowController::getTexture( "gTextTexture" );

    // free loaded images
    gDotTexture->free();
    gObsTexture->free();
    gTextTexture->free();

    TTF_CloseFont( gFont );
    gFont = NULL;

    // destroy window    
    SDL_DestroyRenderer( gRenderer );
    SDL_DestroyWindow( gWindow );
    gWindow = NULL;
    gRenderer = NULL;

    // quit SDL subsystems
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}