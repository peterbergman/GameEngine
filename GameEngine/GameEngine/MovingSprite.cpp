#include "MovingSprite.h"
#include <iostream>
#include <string>

// Factory function to control object creation.
MovingSprite* MovingSprite::GetInstance(std::string tag, std::string file_name, int x_pos, int y_pos, int width, int height, int dx, int dy) {
    return new MovingSprite(tag, file_name, x_pos, y_pos, width, height, dx, dy);
}

MovingSprite::MovingSprite(std::string tag, std::string file_name, int x_pos, int y_pos, int width, int height, int dx, int dy):dx(dx), dy(dy), Sprite(tag, x_pos, y_pos, width, height, file_name) {
}

// Draws the sprite with the specified change in x and y each iteration of the main event loop.
void MovingSprite::Draw(int time_elapsed) {
    boundary->x = boundary->x + dx;
    boundary->y = boundary->y + dy;
    SDL_RenderCopy(renderer, texture, NULL, boundary);
}

MovingSprite::~MovingSprite() {
    delete boundary;
    SDL_DestroyTexture(texture);
}