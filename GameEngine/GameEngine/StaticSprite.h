#ifndef __EngineX__StaticSprite__
#define __EngineX__StaticSprite__

#include <string>
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include "Sprite.h"

// Class to represent static sprites.
class StaticSprite : public Sprite {
    
public:
    
    // Factory function to control object creation.
    static StaticSprite* GetInstance(std::string tag, std::string file_name, int x_pos, int y_pos, int width, int height);
    
    // Draws a static image representing the sprite.
    virtual void Draw(int time_elapsed);
    
    virtual ~StaticSprite();
private:
    StaticSprite(std::string tag, std::string file_name, int x_pos, int y_pos, int width, int height); // Guard against value semantic
    StaticSprite(const StaticSprite& other_sprite); // Guard against value semantic
    const StaticSprite& operator=(const StaticSprite& other_sprite); // Guard against value semantic
};

#endif
