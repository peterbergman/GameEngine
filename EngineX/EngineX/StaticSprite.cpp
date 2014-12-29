#include "StaticSprite.h"
#include <iostream>
#include <string>

StaticSprite* StaticSprite::GetInstance(std::string file_name, int x_pos, int y_pos, int width, int height) {
    return new StaticSprite(file_name, x_pos, y_pos, width, height);
}

StaticSprite::StaticSprite(std::string file_name, int x_pos, int y_pos, int width, int height):Sprite(x_pos, y_pos, width, height, file_name) {
    
}

void StaticSprite::Draw() {
    SDL_RenderCopy(renderer, texture, NULL, boundary);
}

StaticSprite::~StaticSprite() {
    delete boundary;
    SDL_DestroyTexture(texture);
}
