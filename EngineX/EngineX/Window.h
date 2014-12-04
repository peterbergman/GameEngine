#ifndef __EngineX__Window__
#define __EngineX__Window__

#include <iostream>
#include <vector>
#include <string>
#include <SDL2/SDL.h>

class Sprite;
class Window {
public:
    Window(std::string, int, int);
    SDL_Renderer* GetRenderer();
    void AddSprite(Sprite*);
    ~Window();
private:
    int height, width;
    std::string title;
    SDL_Window* window;
    SDL_Renderer* renderer;
    std::vector<Sprite*> sprites;
    void InitSDL();
    void SetUpRenderer();
    void SetUpWindow();
};

#endif
