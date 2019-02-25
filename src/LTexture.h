#ifndef LTEXTURE_H
#define LTEXTURE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

// texture wrapper class
class LTexture
{
public:
    LTexture();

    ~LTexture();

    // loads image from path
    bool loadFromFile( SDL_Renderer* gRenderer, std::string path );
    bool loadFromFile( SDL_Renderer* gRenderer, std::string path, float dimensionX, float dimensionY );
    
    // create image from font string
    bool loadFromRenderedText( SDL_Renderer* gRenderer, TTF_Font* gFont, std::string textureText, SDL_Color textColor );

    // deallocates texture
    void free();

    // set color modulation
    void setColor( Uint8 red, Uint8 green, Uint8 blue );

    // set blending
    void setBlendMode( SDL_BlendMode blending );

    // set alpha modulation
    void setAlpha( Uint8 alpha );
    
    // renders texture at given point
    void render( SDL_Renderer* gRenderer, int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE );

    // getters
    int getWidth();
    int getHeight();

    SDL_Texture* getTexture();

private:
    SDL_Texture* mTexture;

    int mWidth;
    int mHeight;
};


#endif /* LTEXTURE_H */