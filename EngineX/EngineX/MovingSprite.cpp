#include "MovingSprite.h"
#include <iostream>
#include <string>

MovingSprite* MovingSprite::GetInstance(std::string file_name, int x_pos, int y_pos, int width, int height, int dx, int dy) {
    return new MovingSprite(file_name, x_pos, y_pos, width, height, dx, dy);
}

MovingSprite::MovingSprite(std::string file_name, int x_pos, int y_pos, int width, int height, int dx, int dy):dx(dx), dy(dy), Sprite(x_pos, y_pos, width, height, file_name) {
    
}

void MovingSprite::Draw() {
    boundary->x = boundary->x + dx;
    boundary->y = boundary->y + dy;
    SDL_RenderCopy(renderer, texture, NULL, boundary);
}

MovingSprite::~MovingSprite() {
    delete boundary;
    SDL_DestroyTexture(texture);
}