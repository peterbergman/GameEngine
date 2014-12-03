#ifndef __EngineX__Engine__
#define __EngineX__Engine__

#include <stdio.h>
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_ttf/SDL_ttf.h>
#include <string>
#include "Window.h"

namespace enginex {
    class Engine {
    public:
        Engine(std::string);
        ~Engine();
    private:
        bool is_running;
        Window* window;
        void Run();
        void Quit();
    };
}
#endif
