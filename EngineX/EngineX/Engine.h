#ifndef __EngineX__Engine__
#define __EngineX__Engine__

#include <iostream>
#include <string>
#include <map>
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_ttf/SDL_ttf.h>
#include "Sprite.h"
#include "ImageSprite.h"
#include "Window.h"

typedef void (*collision_listener)(Sprite*,Sprite*);
typedef void (*time_event_listener)(SDL_Event);

class Engine {
public:
    Engine(std::string, int, int, int);
    void Run();
    void AddSprite(Sprite*);
    void RemoveSprite(Sprite*);
    void SetCollisionListener(collision_listener);
    int GetWindowWidth();
    int GetWindowHeight();
    void AddTimeEventListener(time_event_listener, int);
    void SetScene(std::string);
    static Uint32 time_event_type;
    ~Engine();
private:
    bool is_running;
    Window* window;
    int fps;
    int frame_counter;
    collision_listener current_collision_listener;
    std::map<int, time_event_listener> time_event_listeners;
    void Quit();
    void PollEvent();
    void RegisterTimeEvent();
    void DetectCollision();
    void HandleTimeEvent(SDL_Event);
};
#endif
