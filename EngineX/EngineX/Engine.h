#ifndef __EngineX__Engine__
#define __EngineX__Engine__

#include <iostream>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_ttf/SDL_ttf.h>
#include "Sprite.h"
#include "ImageSprite.h"
#include "Window.h"

typedef void (*collision_listener)(Sprite*,Sprite*);

class Engine {
public:
    Engine(std::string, int);
    void Run();
    void AddSprite(Sprite*);
    void RemoveSprite(Sprite*);
    void SetCollisionListener(collision_listener);
    static Uint32 time_event_type;
    ~Engine();
private:
    bool is_running;
    Window* window;
    int fps;
    int frame_counter;
    collision_listener current_collision_listener;
    void Quit();
    void PollEvent();
    void RegisterTimeEvent();
    void DetectCollision();
};
#endif
