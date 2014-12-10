#ifndef __EngineX__Window__
#define __EngineX__Window__

#include <iostream>
#include <vector>
#include <string>
#include <SDL2/SDL.h>
#include "Sprite.h"

class Window {
public:
    Window(std::string, int, int);
    SDL_Renderer* GetRenderer();
    void AddSprite(Sprite*);
    void RemoveSprite(Sprite*);
    std::vector<Sprite*> GetSprites();
    void DrawSprites();
    void PropagateEventToSprites(SDL_Event);
    int GetWidth();
    int GetHeight();
    void SetBackground(std::string);
    ~Window();
private:
    int height, width;
    std::string title;
    SDL_Window* window;
    SDL_Renderer* renderer;
    std::vector<Sprite*> sprites;
    void InitSDL();
    void InitSDLImage();
    void SetUpRenderer();
    void SetUpWindow();
    bool Contains(int, int);
    bool Contains(Sprite*);
};

#endif
