#ifndef __EngineX__Engine__
#define __EngineX__Engine__

#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_ttf/SDL_ttf.h>

class Engine {
public:
    void run();
private:
    bool is_running;
};
#endif
