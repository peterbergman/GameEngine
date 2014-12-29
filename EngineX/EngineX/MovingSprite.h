#ifndef __EngineX__MovingSprite__
#define __EngineX__MovingSprite__

#include <string>
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include "Sprite.h"

class MovingSprite : public Sprite {
public:
    static MovingSprite* GetInstance(std::string, int, int, int, int, int, int);
    virtual void Draw();
    virtual ~MovingSprite();
private:
    MovingSprite(std::string, int, int, int, int, int, int); // Guard against value semantic
    MovingSprite(const MovingSprite&); // Guard against value semantic
    const MovingSprite& operator=(const MovingSprite&); // Guard against value semantic
    int dx, dy;
};

#endif
