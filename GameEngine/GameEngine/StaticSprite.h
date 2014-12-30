#ifndef __EngineX__StaticSprite__
#define __EngineX__StaticSprite__

#include <string>
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include "Sprite.h"

class StaticSprite : public Sprite {
public:
    static StaticSprite* GetInstance(std::string, int, int, int, int);
    virtual void Draw(int time_elapsed);
    virtual ~StaticSprite();
private:
    StaticSprite(std::string, int, int, int, int); // Guard against value semantic
    StaticSprite(const StaticSprite&); // Guard against value semantic
    const StaticSprite& operator=(const StaticSprite&); // Guard against value semantic
};

#endif
