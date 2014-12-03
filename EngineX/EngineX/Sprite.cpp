#include "Sprite.h"
namespace enginex {
    
    Sprite::Sprite(std::string file_name, int x_pos, y_pos) {
        SDL_Surface* surface = IMG_Load(file_name.c_str());
        if (surface == nullptr) { // TODO: throw exception to application
            std::cout << "Could not load image... :(" << std::endl;
        } else {
            texture = SDL_CreateTextureFromSurface(enginex_window->GetRenderer(), surface);
            SDL_FreeSurface(surface);
            if (texture == nullptr) { // TODO: throw exception to application
                std::cout << "Could not create texture... :(" << std::endl;
            }
        }
    }
    
    Sprite::~Sprite() {
        SDL_DestroyTexture(texture);
    }
}