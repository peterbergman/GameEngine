#ifndef __EngineX__Engine__
#define __EngineX__Engine__

#include <iostream>
#include <string>
#include <map>
#include <functional>
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_ttf/SDL_ttf.h>
#include "Sprite.h"
#include "StaticSprite.h"
#include "MovingSprite.h"
#include "AnimatedSprite.h"
#include "Level.h"
#include "Window.h"

typedef void (*collision_listener)(Sprite*,Sprite*);

// The core class of the GameEngine framework. Handles the main event loop.
class Engine {
    
public:
    
    // Creates a new Engine object and sets the member variable fps.
    // Also creates a new Window object by passing on the width, height and title arguments.
    Engine(std::string game_name, int fps, int window_width, int window_height);
    
    // Starts the main event loop in the game engine.
    // After being called, the engine will be running until the program terminates
    void Run();
    
    // Adds a level to this game engine.
    void AddLevel(Level* level);
    
    // Sets the current level of this game engine.
    void SetCurrentLevel(Level* level);
    
    // Sets the collision listener for the game engine by taking in a function pointer as argument (see collision_listener typedef).
    // The function sent to this function will be called each time a collision is detected.
    // Collisions are evaluated for all sprites on each iteration of the main event loop.
    void SetCollisionListener(std::function<void(Sprite*, Sprite*)> listener);
    
    // Adds a new time event listener to the game engine by taking in a function pointer as argument
    // together with a delay (in milliseconds).
    // This function will then be called repeatedly each time the delay expires. The minimum delay is equal to the fps value. If the delay is set
    // to a value below the fps, then the time event listener will be called in each iteration of the main event loop.
    void AddTimeListener(std::function<void(void)> listener, int delay);
    
    // Adds an action listener that is not connected to any specific sprite.
    void AddEventListener(std::function<void(void)> listener, int key_code);
    
    // Returns the actual time (in milliseconds) that has elapsed since the last iteration of the main event loop (ie. the actual time between two frames).
    double GetTimeElapsed();
   
    // Returns the width of the underlaying window.
    int GetWindowWidth();
    
    // Returns the height of the underlaying window.
    int GetWindowHeight();
    
    // The type ID of events that are emitted as time events. These events are then handled by the time event listeners.
    static Uint32 time_event_type;
    
    ~Engine();
    
private:
    
    // Forces the main event loop to terminate in the next iteration.
    void Quit();
    
    // Polls events (input, system or other game engine events) and delegates them to the
    // appropriate handler.
    void PollEvent();
    
    // Emits a new time event that is then polled in the next iteration of the main event loop.
    void EmitTimeEvent();
    
    // Detects collisions between sprites and calls the collision listener (if any).
    void DetectCollision();
    
    // Delegates an event to the correct handler.
    void DelegateEvent(SDL_Event);
    
    // Handles the events (keybord and mouse) emitted by the game engine. Calls the registererd event listeners (if any).
    void HandleEvent(SDL_Event, bool);
    
    // Handles the time events emitted by the game engine. Calls the registererd time listeners (if any).
    void HandleTime(SDL_Event);
    
    // Internal helper function used to calculate the time elapsed between two main loop iterations.
    long GetTimestamp();
    
    // Sets the actual time that has elapsed since the last iteration of the main event loop (ie. the actual time between two frames).
    void SetTimeElapsed(long, long);
    
    // Flag that control the main event loop. The loop will be running as long as this flag is set to true.
    bool is_running;
    
    // A pointer to the underlaying window object, used to delegate calls such as adding new sprites etc.
    Window* window;
    
    // The number of frame updates per second.
    int fps;
    
    // A counter that is increased by 1 for each frame update, the value is then added to the time event emitted by the game engine.
    int frame_counter;
    
    // The collision listener function registered (if any).
    std::function<void(Sprite*, Sprite*)> current_collision_listener;
    
    // A data structure to hold all time event listeners registererd (if any) together with the delay for each listener.
    std::map<int, std::function<void(void)>> time_listeners;
    
    // A data structure to hold all action event listeners registererd (if any) together with the keycode for each listener.
    std::map<int, std::function<void(void)>> event_listeners;
    
    // A data structure to hold all levels added (if any) to this game engine.
    std::vector<Level*> levels;
    
    // The actual time that has elapsed since the last iteration of the main event loop (ie. the actual time between two frames).
    double time_elapsed;
    
    // The current level.
    Level* current_level;
};
#endif
