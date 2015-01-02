#include "StaticSprite.h"
#include <iostream>
#include <string>

// Factory function to control object creation.
StaticSprite* StaticSprite::GetInstance(std::string file_name, int x_pos, int y_pos, int width, int height) {
    return new StaticSprite(file_name, x_pos, y_pos, width, height);
}

StaticSprite::StaticSprite(std::string file_name, int x_pos, int y_pos, int width, int height):Sprite(x_pos, y_pos, width, height, file_name) {
    
}

// Draws a static image representing the sprite.
void StaticSprite::Draw(int time_elapsed) {
    SDL_RenderCopy(renderer, texture, NULL, boundary);
}

StaticSprite::~StaticSprite() {
}
