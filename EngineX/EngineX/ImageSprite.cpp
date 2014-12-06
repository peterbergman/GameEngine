#include "ImageSprite.h"
#include <iostream>
#include <string>

ImageSprite::ImageSprite(std::string file_name, int x_pos, int y_pos, int width, int height):Sprite(x_pos, y_pos, width, height), file_name(file_name) {
    
}

void ImageSprite::Draw() {
    SDL_RenderCopy(renderer, texture, NULL, boundary);
}

void ImageSprite::SetUpTexture() {
    SDL_Surface* surface = IMG_Load(file_name.c_str());
    if (surface == nullptr) { // TODO: throw exception to application
        std::cout << "Could not load image... :(" << std::endl;
    } else {
        texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_FreeSurface(surface);
        if (texture == nullptr) { // TODO: throw exception to application
            std::cout << "Could not create texture... :(" << std::endl;
        }
    }
}

ImageSprite::~ImageSprite() {
    delete boundary;
    SDL_DestroyTexture(texture);
}
