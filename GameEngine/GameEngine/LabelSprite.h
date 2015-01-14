#ifndef __GameEngine__LabelSprite__
#define __GameEngine__LabelSprite__

#include <string>
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_ttf/SDL_ttf.h>
#include "Sprite.h"

// Class to represent text labels.
class LabelSprite : public Sprite {
    
    public:
    
    // Factory function to control object creation.
    static LabelSprite* GetInstance(std::string tag, std::string message, int x_pos, int y_pos);
    
    // Draws a static image representing the sprite.
    virtual void Draw(int);
    
    virtual ~LabelSprite();
    
    private:
    LabelSprite(std::string tag, std::string message, int x_pos, int y_pos); // Guard against value semantic
    
    LabelSprite(const LabelSprite& other_sprite); // Guard against value semantic
    
    const LabelSprite& operator=(const LabelSprite& other_sprite); // Guard against value semantic
    
    // The message to show.
    std::string message;
    
};
#endif
