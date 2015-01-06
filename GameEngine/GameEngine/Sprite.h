
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
    
public:
    
    // Sets the renderer member variable.
    void SetRenderer(SDL_Renderer* renderer);
    
    // Adds an event listener to the sprite.
    void AddEventListener(std::function<void(SDL_Event, Sprite*)> listener, int key_code);
    
    // Adds a time listener to the sprite with a delay specified in milliseconds.
    void AddTimeListener(std::function<void(Sprite*)> listener, int delay);
    
    // Sets the X value of the upper right coordinate for the sprite.
    void SetX(int x);
    
    // Sets the Y value of the upper right coordinate for the sprite.
    void SetY(int y);
    
    // Returns the X value of the upper right coordinate for the sprite.
    int GetX();
    
    // Returns the Y value of the upper right coordinate for the sprite.
    int GetY();
    
    // Returns the width of the sprite.
    int GetWidth();

    // Returns the height of the sprite.
    int GetHeight();
    
    // Returns the tag of the sprite.
    std::string GetTag();
    
    void SetIsRemoved(bool is_removed);
    
    bool GetIsRemoved();
    
    // Delegates an event to the correct handler.
    void DelegateEvent(SDL_Event event);
    
    // Checks if the sprite contain the specified x and y value.
    bool Contains(int x, int y);
    
    // Checks if the sprite contain the specified sprite.
    bool Contains(Sprite* sprite);
    
    // Sets up the texture used by the sprite.
    void SetUpTexture();
    
    // Draws the sprite according to the behavior specified in the subclass.
    virtual void Draw(int time_elapsed) = 0;
    
    virtual ~Sprite();
    
protected:
    
    // Protected in order to guard against value semantics but still allows for creating subclasses.
    Sprite(std::string tag, int x_pos, int y_pos, int width, int height, std::string file_name);
    
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
    Sprite(const Sprite& other_sprite);
    
    // Private in order to guard against value semantics.
    const Sprite& operator=(const Sprite& other_sprite);
    
    // Internal helper function to which events are delegated.
    void HandleEvent(SDL_Event event, bool mouse_event);
    
    // Internal helper function to which time events are delegated.
    void HandleTime(SDL_Event event);
    
    // Map containng all event listeners added for the sprite and the keycode for each listener.
    std::map<int, std::function<void(SDL_Event, Sprite*)>> event_listeners;
    
    // Map containng all time listeners added for the sprite and the delay for each listener.
    std::map<int, std::function<void(Sprite*)>> time_listeners;
    
    // A tag added to the sprite which can be used when evaluating collisions.
    std::string tag;
    
    bool is_removed;
};

#endif
