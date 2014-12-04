#include "Sprite.h"
Sprite::Sprite(std::string file_name, int x_pos, int y_pos) {
    SDL_Surface* surface = IMG_Load(file_name.c_str());
    if (surface == nullptr) { // TODO: throw exception to application
        std::cout << "Could not load image... :(" << std::endl;
    } else {
        texture = SDL_CreateTextureFromSurface(window->GetRenderer(), surface);
        SDL_FreeSurface(surface);
        if (texture == nullptr) { // TODO: throw exception to application
            std::cout << "Could not create texture... :(" << std::endl;
        }
    }
}

void Sprite::SetWindow(Window* window) {
    this->window = window;
}

void Sprite::Draw() {
    SDL_RenderCopy(window->GetRenderer(), texture, NULL, NULL);
}

Sprite::~Sprite() {
    SDL_DestroyTexture(texture);
}