
#ifndef __EngineX__Sprite__
#define __EngineX__Sprite__

#include <iostream>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include "Window.h"
class Window;
class Sprite {
public:
    Sprite(std::string, int, int);
    void SetWindow(Window*);
    void Draw();
    ~Sprite();
private:
    Window* window;
    SDL_Texture* texture;
};

#endif
