#include "AnimatedSprite.h"
#include <iostream>
#include <string>

AnimatedSprite* AnimatedSprite::GetInstance(std::string file_name, int x_pos, int y_pos, int width, int height) {
    return new AnimatedSprite(file_name, x_pos, y_pos, width, height);
}

AnimatedSprite::AnimatedSprite(std::string file_name, int x_pos, int y_pos, int width, int height):Sprite(x_pos, y_pos, width, height, file_name) {
    
}

void AnimatedSprite::Draw() {
    SDL_RenderCopy(renderer, texture, NULL, boundary);
}

AnimatedSprite::~AnimatedSprite() {
    delete boundary;
    SDL_DestroyTexture(texture);
}
