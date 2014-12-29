
#ifndef __EngineX__Sprite__
#define __EngineX__Sprite__

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>

// Root class for sprite class hierarchy. This class is not supposed to be instantiated directly.
// Instead subclasses are used for different types of sprites.
class Sprite {

typedef void (*action_listener)(SDL_Event, Sprite*);
public:
    
    // Sets the renderer member variable.
    void SetRenderer(SDL_Renderer*);
    
    // Adds an action listener to the sprite.
    void AddActionListener(action_listener);
    
    // Adds a time event listener to the sprite with a delay specified in milliseconds.
    void AddTimeEventListener(action_listener, int);
    
    // Handles an event sent to the sprite.
    void HandleEvent(SDL_Event);
    
    // Sets the X value of the upper right coordinate for the sprite.
    void SetX(int);
    
    // Sets the Y value of the upper right coordinate for the sprite.
    void SetY(int);
    
    // Returns the X value of the upper right coordinate for the sprite.
    int GetX();
    
    // Returns the Y value of the upper right coordinate for the sprite.
    int GetY();
    
    // Returns the width of the sprite.
    int GetWidth();

    // Returns the height of the sprite.
    int GetHeight();
    
    // Checks if the sprite contain the specified x and y value.
    bool Contains(int, int);
    
    // Checks if the sprite contain the specified sprite.
    bool Contains(Sprite*);
    
    // Sets up the texture used by the sprite.
    void SetUpTexture();
    
    // Draws the sprite according to the behavior specified in the subclass.
    virtual void Draw(int) = 0;
    
    virtual ~Sprite();
protected:
    
    // Protected in order to guard against value semantics but still allows for creating subclasses.
    Sprite(int, int, int, int, std::string);
    
    // The renderer for the window to which the sprite is added.
    SDL_Renderer* renderer;
    
    // The boundary for which the sprite is contained within.
    SDL_Rect* boundary;
    
    // The file name for the image shown on screen for the sprite.
    std::string file_name;
    
    // The texture for the image shown on screen for the sprite.
    SDL_Texture* texture;
private:
    // Private in order to guard against value semantics.
    Sprite(const Sprite&);
    
    // Private in order to guard against value semantics.
    const Sprite& operator=(const Sprite&);
    
    // Internal helper function to which action events are delegated.
    void HandleActionEvent(SDL_Event, bool);
    
    // Internal helper function to which time events are delegated.
    void HandleTimeEvent(SDL_Event);
    
    // Vector containng all action event listeners added for the sprite.
    std::vector<action_listener> action_event_listeners;
    
    // Map containng all time event listeners added for the sprite and the delay for each listener.
    std::map<int, action_listener> time_event_listeners;
};

#endif
