#include "Sprite.h"
Sprite::Sprite(std::string file_name, int x_pos, int y_pos, int height, int width) {
    boundary = new SDL_Rect();
    boundary->x = x_pos;
    boundary->y = y_pos;
    boundary->h = height;
    boundary->w = width;
    this->file_name = file_name;
}

void Sprite::SetRenderer(SDL_Renderer* renderer) {
    this->renderer = renderer;
}

void Sprite::Draw() {
    SDL_RenderCopy(renderer, texture, NULL, boundary);
}

void Sprite::SetUpTexture() {
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

Sprite::~Sprite() {
    delete boundary;
    SDL_DestroyTexture(texture);
}