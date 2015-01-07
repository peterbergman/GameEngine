#include "LabelSprite.h"

LabelSprite* LabelSprite::GetInstance(std::string tag, std::string message, int x_pos, int y_pos) {
    return new LabelSprite(tag, message, x_pos, y_pos);
}

LabelSprite::LabelSprite(std::string tag, std::string message, int x_pos, int y_pos):message(message), Sprite(tag, x_pos, y_pos, 25 * message.length(), 50, "") {
    font = TTF_OpenFont("/Users/Peter/Documents/DSV/Prog3/images/gameengine/font.ttf", 48);
    TTF_SetFontOutline(font, 1);
}

void LabelSprite::Draw(int elapsed_time) {
    SDL_DestroyTexture(texture);
    SDL_Color white = { 255, 255, 255 };
    SDL_Surface* message_surface = TTF_RenderText_Solid(font, message.c_str(), white);
    texture = SDL_CreateTextureFromSurface(renderer, message_surface);
    SDL_FreeSurface(message_surface);
    SDL_RenderCopy(renderer, texture, NULL, &boundary);
}

LabelSprite::~LabelSprite() {
    TTF_CloseFont(font);
}

