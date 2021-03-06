#include "LabelSprite.h"
#include "Window.h"

LabelSprite* LabelSprite::GetInstance(std::string tag, std::string message, int x_pos, int y_pos) {
    return new LabelSprite(tag, message, x_pos, y_pos);
}

LabelSprite::LabelSprite(std::string tag, std::string message, int x_pos, int y_pos):message(message), Sprite(tag, x_pos, y_pos, 25 * message.length(), 50, "") {
}

void LabelSprite::Draw(int elapsed_time) {
    SDL_DestroyTexture(texture);
    SDL_Color white = { 255, 255, 255 };
    SDL_Surface* message_surface = TTF_RenderText_Solid(window->GetFont(), message.c_str(), white);
    texture = SDL_CreateTextureFromSurface(window->GetRenderer(), message_surface);
    SDL_FreeSurface(message_surface);
    SDL_RenderCopy(window->GetRenderer(), texture, NULL, &boundary);
}

LabelSprite::~LabelSprite() {
}

