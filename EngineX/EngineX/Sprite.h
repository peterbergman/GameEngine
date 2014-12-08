
#ifndef __EngineX__Sprite__
#define __EngineX__Sprite__

#include <iostream>
#include <string>
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include "ActionEvent.h"

typedef void (*action_listener)(ActionEvent);

class Sprite {
public:
    Sprite(int, int, int, int);
    void SetRenderer(SDL_Renderer*);
    virtual void SetUpTexture() = 0;
    void AddActionListener(action_listener);
    void HandleEvent(ActionEvent);
    virtual void Draw() = 0;
    virtual ~Sprite();
protected:
    SDL_Renderer* renderer;
    SDL_Rect* boundary;
    std::vector<action_listener> action_listeners;
};

#endif
