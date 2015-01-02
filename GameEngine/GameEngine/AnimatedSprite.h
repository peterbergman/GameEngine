#ifndef __EngineX__AnimatedSprite__
#define __EngineX__AnimatedSprite__

#include <string>
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include "Sprite.h"

// Class to represent animated sprites.
class AnimatedSprite : public Sprite {
    
public:
    
    // Factory function to control object creation.
    static AnimatedSprite* GetInstance(std::vector<std::string> images, int image_change_delay, int x_pos, int y_pos, int width, int height);
    
    // Draws the sprite changing between each image in the image vector with a given delay.
    virtual void Draw(int);
    
    virtual ~AnimatedSprite();
private:
    AnimatedSprite(std::vector<std::string> images, int image_change_delay, int x_pos, int y_pos, int width, int height); // Guard against value semantic
    AnimatedSprite(const AnimatedSprite& other_sprite); // Guard against value semantic
    const AnimatedSprite& operator=(const AnimatedSprite& other_sprite); // Guard against value semantic
    std::vector<std::string> images;
    int image_change_delay, image_index;
    double time_since_last_draw;
};

#endif
