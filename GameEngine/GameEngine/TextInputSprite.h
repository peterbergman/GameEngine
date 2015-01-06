#ifndef __GameEngine__TextInputSprite__
#define __GameEngine__TextInputSprite__

#include <string>
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_ttf/SDL_ttf.h>
#include "Sprite.h"

// Class to represent text input sprites.
class TextInputSprite : public Sprite {
    
public:
    
    // Factory function to control object creation.
    static TextInputSprite* GetInstance(std::string tag, int x_pos, int y_pos);
    
    // Draws a static image representing the sprite.
    virtual void Draw(int);
    
    virtual ~TextInputSprite();
private:
    TextInputSprite(std::string tag, int x_pos, int y_pos); // Guard against value semantic
    
    TextInputSprite(const TextInputSprite& other_sprite); // Guard against value semantic
    
    const TextInputSprite& operator=(const TextInputSprite& other_sprite); // Guard against value semantic
    
    // Internal handler for text input events.
    void HandleTextInput(SDL_Event event);
    
    // The font.
    TTF_Font* font;
    
    // The current text of the input field.
    std::string text;
    
};
#endif
