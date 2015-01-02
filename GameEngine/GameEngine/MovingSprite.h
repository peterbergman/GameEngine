#ifndef __EngineX__MovingSprite__
#define __EngineX__MovingSprite__

#include <string>
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include "Sprite.h"

// Class to represent moving sprites.
class MovingSprite : public Sprite {
    
public:
    
    // Factory function to control object creation.
    static MovingSprite* GetInstance(std::string file_name, int x_pos, int y_pos, int width, int height, int dx, int dy);
    
    // Draws the sprite with the specified change in x and y each iteration of the main event loop.
    virtual void Draw(int);
    
    virtual ~MovingSprite();
private:
    MovingSprite(std::string file_name, int x_pos, int y_pos, int width, int height, int dx, int dy); // Guard against value semantic
    MovingSprite(const MovingSprite& other_sprite); // Guard against value semantic
    const MovingSprite& operator=(const MovingSprite& other_sprite); // Guard against value semantic
    int dx, dy;
};

#endif
