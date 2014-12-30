#ifndef __GameEngine__Level__
#define __GameEngine__Level__

#include "Sprite.h"
#include "StaticSprite.h"
//#include "Window.h"

class Window;

class Level {
public:
    
    Level();
    
    // Adds a new sprite to this level by taking in a sprite pointer as argument.
    void AddSprite(Sprite*); // TODO: implement layers? Could maybe be done with a tree set to hold the sprites instead of a vector
    
    // Removes an existing sprite from this level by taking in a sprite pointer as argument.
    // Frees any memory associated with the sprite object.
    void RemoveSprite(Sprite*);
    
    // Returns a vector of all sprites that have been added to the level.
    std::vector<Sprite*> GetSprites();
    
    // Sets the background of the level by loading the image located at the the path specified as argument.
    void SetBackground(std::string);
    
    // Sets the loaded flag of this level.
    void SetLoaded(bool);
    
    // Sets the window pointer needed to load more sprites is new ones are added after the level is loaded.
    void SetWindow(Window*);
    
    // Delegates an event to the sprites that have been added to the level.
    void PropagateEventToSprites(SDL_Event);
    
    ~Level();
    
private:
    
    // A vector that contains all sprites that have been added to this level.
    std::vector<Sprite*> sprites;
    
    // A flag to indiciate if this level is currently loaded or not
    bool is_loaded;
    
    // A pointer to the window that this level is loaded in.
    Window* window;
};

#endif
