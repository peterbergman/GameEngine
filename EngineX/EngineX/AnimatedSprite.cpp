#include "AnimatedSprite.h"
#include <iostream>
#include <string>

AnimatedSprite* AnimatedSprite::GetInstance(std::vector<std::string> images, int image_change_delay, int x_pos, int y_pos, int width, int height) {
    return new AnimatedSprite(images, image_change_delay, x_pos, y_pos, width, height);
}

AnimatedSprite::AnimatedSprite(std::vector<std::string> images, int image_change_delay, int x_pos, int y_pos, int width, int height):images(images), image_change_delay(image_change_delay), time_since_last_draw(0), image_index(0), Sprite(x_pos, y_pos, width, height, images[0]) {
    
}

void AnimatedSprite::Draw(int time_elapsed) {
    time_since_last_draw = time_since_last_draw + time_elapsed;
    if (time_since_last_draw >= image_change_delay) {
        file_name = images[image_index];
        SetUpTexture(); //TODO: this could probably be optimized so that all textures needed are loaded once
        image_index = (image_index == images.size() - 1 ? 0 : image_index + 1);
        time_since_last_draw = 0;
    }
    SDL_RenderCopy(renderer, texture, NULL, boundary);
}

AnimatedSprite::~AnimatedSprite() {
    delete boundary;
    SDL_DestroyTexture(texture);
}
