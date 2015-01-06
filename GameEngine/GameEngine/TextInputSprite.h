#ifndef __GameEngine__TextInputSprite__
#define __GameEngine__TextInputSprite__

#include <string>
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_ttf/SDL_ttf.h>
#include "Sprite.h"

// Class to represent text input sprites.
class TextInputSprite : public Sprite {
    
public:
    
    // Factory function to control object creation.
    static TextInputSprite* GetInstance(std::string tag, std::string message);
    
    // Draws a static image representing the sprite.
    virtual void Draw(int);
    
    virtual ~TextInputSprite();
private:
    TextInputSprite(std::string tag, std::string message); // Guard against value semantic
    
    TextInputSprite(const TextInputSprite& other_sprite); // Guard against value semantic
    
    const TextInputSprite& operator=(const TextInputSprite& other_sprite); // Guard against value semantic
    
    // Internal handler for text input events.
    void HandleTextInput(SDL_Event event);
    
    // The boundary for which the message is contained within.
    SDL_Rect* message_boundary;
    
    // The boundary for which the text is contained within.
    SDL_Rect* text_boundary;
    
    // The texture for the message shown in the sprite.
    SDL_Texture* message_texture;
    
    // The texture for the text shown in the sprite.
    SDL_Texture* text_texture;
    
    // The font.
    TTF_Font* font;
    
    // The initial message to show.
    std::string message;
    
    // The current text of the input field.
    std::string text;
    
};
#endif
