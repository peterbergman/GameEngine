#ifndef __GameEngine__Level__
#define __GameEngine__Level__

#include "Sprite.h"
#include "StaticSprite.h"

class Window; // Forward declaration neeeded to avoid cyclic dependency.

class Level {
public:
    
    Level(int goal);
    
    // Adds a new sprite to this level by taking in a sprite pointer as argument.
    void AddSprite(Sprite* sprite); // TODO: implement layers? Could maybe be done with a tree set to hold the sprites instead of a vector
    
    // Removes an existing sprite from this level by taking in a sprite pointer as argument.
    // Frees any memory associated with the sprite object.
    void RemoveSprite(Sprite* sprite);
    
    void CleanUpSprites();
    
    // Returns a vector of all sprites that have been added to the level.
    std::vector<Sprite*> GetSprites();
    
    // Sets the background of the level by loading the image located at the the path specified as argument.
    void SetBackground(std::string background_image_path);
    
    // Sets the loaded flag of this level.
    void SetLoaded(bool is_loaded);
    
    // Sets the window pointer needed to load more sprites is new ones are added after the level is loaded.
    void SetWindow(Window*);
    
    // Returns the goal set for this level.
    int GetGoal();
    
    // Adds a new time event listener to the level by taking in a fee function pointer as argument (see collision_listener typedef)
    // together with a delay (in milliseconds).
    // This function will then be called repeatedly each time the delay expires. The minimum delay is equal to the fps value. If the delay is set
    // to a value below the fps, then the time event listener will be called in each iteration of the main event loop.
    void AddTimeListener(std::function<void(void)> listener, int delay);
    
    // Receives an event and delegates it.
    void DelegateEvent(SDL_Event event);
    
    ~Level();
    
private:
    
    // Handles the time events emitted by the game engine. Calls the registererd time listeners (if any).
    void HandleTime(SDL_Event event);
    
    // A vector that contains all sprites that have been added to this level.
    std::vector<Sprite*> sprites;
    
    // A flag to indiciate if this level is currently loaded or not
    bool is_loaded;
    
    // A pointer to the window that this level is loaded in.
    Window* window;
    
    // A data structure to hold all time event listeners registererd (if any) together with the delay for each listener.
    std::map<int, std::function<void(void)>> time_listeners;
    
    // The goal for this level, specified with an integer.
    int goal;
};

#endif
