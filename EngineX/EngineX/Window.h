#ifndef __EngineX__Window__
#define __EngineX__Window__

#include <iostream>
#include <vector>
#include <string>
#include <SDL2/SDL.h>
#include "Sprite.h"

// The underlaying window used by the game engine.
class Window {
public:
    
    // Creates a new window object and sets the member variable title based on the string sent as argument
    // and boundary as well as height and width based on the height and width sent as arguments.
    Window(std::string, int, int);
    
    // Returns the renderer used by the window.
    SDL_Renderer* GetRenderer();
    
    // Adds a new sprite to the internal window by taking in a sprite pointer as argument.
    void AddSprite(Sprite*);
    
    // Removes an existing sprite from the window by taking in a sprite pointer as argument.
    // Frees any memory associated with the sprite object.
    void RemoveSprite(Sprite*);
    
    // Returns a vector of all sprites that have been added to the window.
    std::vector<Sprite*> GetSprites();
    
    // Renders all sprites that have been added to the window and that are positioned wihtin the window.
    // Deletes any sprite that is positioned outside the window and frees any memory associated with the sprite object.
    void DrawSprites();
    
    // Delegates an event to the sprites that have been added to the window.
    void PropagateEventToSprites(SDL_Event);
    
    // Returns the width of the window.
    int GetWidth();
    
    // Returns the height of the window.
    int GetHeight();
    
    // Sets the background of the window by loading the image located at the the path specified as argument.
    void SetBackground(std::string);
    
    ~Window();
private:
    
    // Internal helper function to initiate SDL.
    void InitSDL();
    
    // Internal helper function to initiate SDL_Image.
    void InitSDLImage();
    
    // Internal helper function to set up a renderer for the window.
    void SetUpRenderer();
    
    // Internal helper function to set up the actual window.
    void SetUpWindow();
    
    // Internal helper function to check if the window contain the specified x and y value.
    bool Contains(int, int);
    
    // Internal helper function to check if the window contain the specified sprite.
    bool Contains(Sprite*);
    
    // The height and width of the window.
    int height, width;
    
    // The title of the window.
    std::string title;
    
    // A pointer to the underlaying SDL_Window object.
    SDL_Window* window;
    
    // The renderer.
    SDL_Renderer* renderer;
    
    // A vector that contains all sprites that have been added to the window.
    std::vector<Sprite*> sprites;
};

#endif
