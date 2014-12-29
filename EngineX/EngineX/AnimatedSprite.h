#ifndef __EngineX__AnimatedSprite__
#define __EngineX__AnimatedSprite__

#include <string>
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include "Sprite.h"

class AnimatedSprite : public Sprite {
public:
    static AnimatedSprite* GetInstance(std::string, int, int, int, int);
    virtual void Draw();
    virtual ~AnimatedSprite();
private:
    AnimatedSprite(std::string, int, int, int, int); // Guard against value semantic
    AnimatedSprite(const AnimatedSprite&); // Guard against value semantic
    const AnimatedSprite& operator=(const AnimatedSprite&); // Guard against value semantic
};

#endif
