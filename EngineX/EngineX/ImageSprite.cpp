#include "ImageSprite.h"
#include <iostream>
#include <string>

ImageSprite* ImageSprite::GetInstance(std::string file_name, int x_pos, int y_pos, int width, int height) {
    return new ImageSprite(file_name, x_pos, y_pos, width, height);
}

ImageSprite::ImageSprite(std::string file_name, int x_pos, int y_pos, int width, int height):Sprite(x_pos, y_pos, width, height, file_name) {
    
}

void ImageSprite::Draw(int time_elapsed) {
    SDL_RenderCopy(renderer, texture, NULL, boundary);
}

ImageSprite::~ImageSprite() {
    delete boundary;
    SDL_DestroyTexture(texture);
}
