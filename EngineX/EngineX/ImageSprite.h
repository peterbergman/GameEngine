#ifndef __EngineX__ImageSprite__
#define __EngineX__ImageSprite__

#include <string>
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include "Sprite.h"

class ImageSprite : public Sprite {
public:
    ImageSprite(std::string, int, int, int, int);
    void SetUpTexture();
    void Draw();
    ~ImageSprite();
private:
    std::string file_name;
    SDL_Texture* texture;
};

#endif
