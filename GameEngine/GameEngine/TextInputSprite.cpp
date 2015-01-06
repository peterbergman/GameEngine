#include "TextInputSprite.h"

TextInputSprite* TextInputSprite::GetInstance(std::string tag, int x_pos, int y_pos) {
    return new TextInputSprite(tag, x_pos, y_pos);
}

TextInputSprite::TextInputSprite(std::string tag, int x_pos, int y_pos):Sprite(tag, x_pos, y_pos, 12, 50, "") {
    
    std::function<void(SDL_Event, Sprite*)> func = std::bind(&TextInputSprite::HandleTextInput, this, std::placeholders::_1);
    AddEventListener(func, SDL_TEXTINPUT);
    
    font = TTF_OpenFont("/Users/Peter/Documents/DSV/Prog3/images/gameengine/font.ttf", 48);
    TTF_SetFontOutline(font, 1);
}

void TextInputSprite::Draw(int time_elapsed) {
    SDL_RenderCopy(renderer, texture, NULL, boundary);
}

void TextInputSprite::HandleTextInput(SDL_Event event) {
    boundary->w = boundary->w  + 25;
    boundary->x = boundary->x - 12;
    
    text += event.text.text;
    
    if (renderer != nullptr) {
        SDL_Color white = { 255, 255, 255 };
        SDL_DestroyTexture(texture);
        SDL_Surface* text_surface = TTF_RenderText_Solid(font, text.c_str(), white);
        texture = SDL_CreateTextureFromSurface(renderer, text_surface);
        SDL_FreeSurface(text_surface);
    }
    
}

TextInputSprite::~TextInputSprite() {
    delete boundary;
    TTF_CloseFont(font);
    SDL_DestroyTexture(texture);
}
