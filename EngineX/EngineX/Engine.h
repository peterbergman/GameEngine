#ifndef __EngineX__Engine__
#define __EngineX__Engine__

#include <iostream>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_ttf/SDL_ttf.h>
#include "Sprite.h"
#include "Window.h"

class Engine {
public:
    Engine(std::string);
    void AddSprite(Sprite*);
    ~Engine();
private:
    bool is_running;
    Window* window;
    void Run();
    void Quit();
};
#endif
