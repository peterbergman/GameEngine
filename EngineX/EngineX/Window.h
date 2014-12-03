#ifndef __EngineX__Window__
#define __EngineX__Window__

#include <stdio.h>
#include <iostream>
#include <SDL2/SDL.h>

class Window {
public:
    Window(int, int);
    ~Window();
private:
    int height, width;
    SDL_Window* window;
    SDL_Renderer* renderer;
    void InitSDL();
    void SetUpRenderer();
    void SetUpWindow();
};
#endif
