#ifndef __EngineX__Engine__
#define __EngineX__Engine__

#include <iostream>
#include <string>
#include <map>
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_ttf/SDL_ttf.h>
#include "Sprite.h"
#include "StaticSprite.h"
#include "MovingSprite.h"
#include "AnimatedSprite.h"
#include "Window.h"

typedef void (*collision_listener)(Sprite*,Sprite*);
typedef void (*event_listener)();

// The interface part of the game engine. This is the class that the application program
// is interfacing with and all operations on the framework goes through this class.
class Engine {
    
public:
    
    // Creates a new Engine object and sets the member variable fps.
    // Also creates a new Window object by passing on the width, height and title arguments.
    Engine(std::string, int, int, int);
    
    // Starts the main event loop in the game engine.
    // After being called, the engine will be running until the program terminates
    void Run();
    
    // Adds a new sprite to the game engine by taking in a sprite pointer as argument.
    // The sprite will then be shown in the next iteration of the main event loop.
    void AddSprite(Sprite*); // TODO: implement layers? Could maybe be done with a tree set to hold the sprites instead of a vector
    
    // Removes an existing sprite by taking in a sprite pointer as argument.
    // The sprite will then be removed from the screen in the next iteration of the main event loop.
    void RemoveSprite(Sprite*);
    
    // Sets the collision listener for the game engine by taking in a free function pointer as argument (see collision_listener typedef).
    // The function sent to this function will be called each time a collision is detected.
    // Collisions are evaluated for all sprites on each iteration of the main event loop.
    void SetCollisionListener(collision_listener);
    
    // Adds a new time event listener to the game engine by taking in a fee function pointer as argument (see collision_listener typedef)
    // together with a delay (in milliseconds).
    // This function will then be called repeatedly each time the delay expires. The minimum delay is equal to the fps value. If the delay is set
    // to a value below the fps, then the time event listener will be called in each iteration of the main event loop.
    void AddTimeListener(event_listener, int);
    
    // Adds an action listener that is not connected to any specific sprite.
    void AddEventListener(event_listener, int);
    
    // Sets the current background of the underlaying window by taking in a string which is the file name
    // of the image to be loaded as background.
    void SetScene(std::string);
    
    // Returns the actual time (in milliseconds) that has elapsed since the last iteration of the main event loop (ie. the actual time between two frames).
    double GetTimeElapsed();
    
    // Returns the current frame count.
    int GetFrameCounter();
   
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
    
    // Handles the time events emitted by the game engine. Calls the registererd time event listeners (if any).
    void HandleTimeEvent(SDL_Event);
    
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
    collision_listener current_collision_listener;
    
    // A data structure to hold all time event listeners registererd (if any) together with the delay for each listener.
    std::map<int, event_listener> time_listeners;
    
    // A data structure to hold all action event listeners registererd (if any) together with the keycode for each listener.
    std::map<int, event_listener> event_listeners;
    
    // The actual time that has elapsed since the last iteration of the main event loop (ie. the actual time between two frames).
    double time_elapsed;
};
#endif
