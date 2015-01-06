#ifndef __EngineX__Window__
#define __EngineX__Window__

#include <iostream>
#include <vector>
#include <string>
#include "Sprite.h"
#include "StaticSprite.h"

class Level; // Forward declaration neeeded to avoid cyclic dependency.

// The underlaying window used by the game engine.
class Window {
    
public:
    
    // Creates a new window object and sets the member variable title based on the string sent as argument
    // and boundary as well as height and width based on the height and width sent as arguments.
    Window(std::string title, int width, int height);
    
    // Returns the renderer used by the window.
    SDL_Renderer* GetRenderer();

    // Loads all the sprites included in the specified level.
    void LoadLevel(Level* level);
    
    // Loads a spcecific sprite.
    void LoadSprite(Sprite* sprite);
    
    // Renders all sprites that have been added to the window and that are positioned wihtin the window.
    // Deletes any sprite that is positioned outside the window and frees any memory associated with the sprite object.
    void DrawSprites(int time_elapsed);
    
    // Returns the width of the window.
    int GetWidth();
    
    // Returns the height of the window.
    int GetHeight();
    
    ~Window();
    
private:
    
    // Internal helper function to initiate SDL.
    void InitSDL();
    
    // Internal helper function to initiate SDL_Image.
    void InitSDLImage();
    
    // Internal helper function to initiate SDL_ttf.
    void InitSDLttf();
    
    // Internal helper function to set up a renderer for the window.
    void SetUpRenderer();
    
    // Internal helper function to set up the actual window.
    void SetUpWindow();
    
    // Internal helper function to check if the window contain the specified x and y value.
    bool Contains(int x, int y);
    
    // Internal helper function to check if the window contain the specified sprite.
    bool Contains(Sprite* sprite);
    
    // The height and width of the window.
    int height, width;
    
    // The title of the window.
    std::string title;
    
    // A pointer to the underlaying SDL_Window object.
    SDL_Window* window;
    
    // The renderer.
    SDL_Renderer* renderer;
    
    // The current level loaded for this window.
    Level* current_level;
};

#endif
