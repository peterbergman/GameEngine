#ifndef __EngineX__ImageSprite__
#define __EngineX__ImageSprite__

#include <string>
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include "Sprite.h"

class ImageSprite : public Sprite {
public:
    static ImageSprite* GetInstance(std::string, int, int, int, int);
    virtual void Draw(int);
    virtual ~ImageSprite();
private:
    ImageSprite(std::string, int, int, int, int); // Guard against value semantic
    ImageSprite(const ImageSprite&); // Guard against value semantic
    const ImageSprite& operator=(const ImageSprite&); // Guard against value semantic
};

#endif
