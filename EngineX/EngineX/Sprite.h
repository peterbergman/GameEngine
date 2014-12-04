
#ifndef __EngineX__Sprite__
#define __EngineX__Sprite__

#include <iostream>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>

class Sprite {
public:
    Sprite(std::string, int, int, int, int);
    void SetRenderer(SDL_Renderer*);
    void Draw();
    ~Sprite();
private:
    SDL_Renderer* renderer;
    SDL_Texture* texture;
    SDL_Rect* boundary;
    std::string file_name;
};

#endif
