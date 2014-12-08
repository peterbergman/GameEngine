
#ifndef __EngineX__Sprite__
#define __EngineX__Sprite__

#include <iostream>
#include <string>
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>

typedef void (*action_listener)(SDL_Event);

class Sprite {
public:
    Sprite(int, int, int, int);
    void SetRenderer(SDL_Renderer*);
    void AddActionListener(action_listener);
    void HandleEvent(SDL_Event);
    void SetX(int);
    void SetY(int);
    int GetX();
    int GetY();
    virtual void SetUpTexture() = 0;
    virtual void Draw() = 0;
    virtual ~Sprite();
protected:
    SDL_Renderer* renderer;
    SDL_Rect* boundary;
    std::vector<action_listener> action_listeners;
private:
    bool Contains(int, int);
};

#endif
