#ifndef __EngineX__AnimatedSprite__
#define __EngineX__AnimatedSprite__

#include <string>
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include "Sprite.h"

class AnimatedSprite : public Sprite {
public:
    static AnimatedSprite* GetInstance(std::vector<std::string>, int, int, int, int, int);
    virtual void Draw(int);
    virtual ~AnimatedSprite();
private:
    AnimatedSprite(std::vector<std::string>, int, int, int, int, int); // Guard against value semantic
    AnimatedSprite(const AnimatedSprite&); // Guard against value semantic
    const AnimatedSprite& operator=(const AnimatedSprite&); // Guard against value semantic
    std::vector<std::string> images;
    int image_change_delay, image_index;
    double time_since_last_draw;
};

#endif
