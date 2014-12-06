
#ifndef __EngineX__Sprite__
#define __EngineX__Sprite__

#include <iostream>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>

class Sprite {
public:
    Sprite(int, int, int, int);
    void SetRenderer(SDL_Renderer*);
    virtual void SetUpTexture() = 0;
    virtual void Draw() = 0;
    virtual ~Sprite();
protected:
    SDL_Renderer* renderer;
    SDL_Rect* boundary;
};

#endif
