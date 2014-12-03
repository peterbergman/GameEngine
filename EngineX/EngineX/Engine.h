#ifndef __EngineX__Engine__
#define __EngineX__Engine__

#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_ttf/SDL_ttf.h>

class Engine {
public:
    ~Engine();
private:
    bool is_running;
    void run();
    void init();
    void tear_down();
};
#endif
