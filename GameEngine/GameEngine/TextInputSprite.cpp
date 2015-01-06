#include "TextInputSprite.h"

TextInputSprite* TextInputSprite::GetInstance(std::string tag, std::string message) {
    return new TextInputSprite(tag, message);
}

TextInputSprite::TextInputSprite(std::string tag, std::string message):message(message), message_boundary(NULL), message_texture(NULL), text_boundary(NULL), text_texture(NULL), Sprite(tag, 0, 0, 0, 0, "/Users/Peter/Documents/DSV/Prog3/images/gameengine/transparent.png") {
    
    std::function<void(SDL_Event, Sprite*)> func = std::bind(&TextInputSprite::HandleTextInput, this, std::placeholders::_1);
    AddEventListener(func, SDL_TEXTINPUT);
    
    font = TTF_OpenFont("/Users/Peter/Documents/DSV/Prog3/images/gameengine/font.ttf", 48);
    TTF_SetFontOutline(font, 1);
    
    message_boundary = new SDL_Rect();
    message_boundary->x = 400 - (12 * message.length());
    message_boundary->y = 290;
    message_boundary->h = 50;
    message_boundary->w = 25 * message.length();
    
    text_boundary = new SDL_Rect();
    text_boundary->x = 400;
    text_boundary->y = 325;
    text_boundary->h = 50;
    text_boundary->w = 12;
}

void TextInputSprite::Draw(int time_elapsed) {
    SDL_DestroyTexture(message_texture);
    SDL_Color white = { 255, 255, 255 };
    SDL_Surface* message_surface = TTF_RenderText_Solid(font, message.c_str(), white);
    message_texture = SDL_CreateTextureFromSurface(renderer, message_surface);
    SDL_FreeSurface(message_surface);
    
    SDL_RenderCopy(renderer, texture, NULL, NULL);
    SDL_RenderCopy(renderer, message_texture, NULL, message_boundary);
    SDL_RenderCopy(renderer, text_texture, NULL, text_boundary);
}

void TextInputSprite::HandleTextInput(SDL_Event event) {
    text_boundary->w = text_boundary->w  + 25;
    text_boundary->x = text_boundary->x - 12;
    
    text += event.text.text;
    
    if (renderer != nullptr) {
        SDL_Color white = { 255, 255, 255 };
        SDL_DestroyTexture(text_texture);
        SDL_Surface* text_surface = TTF_RenderText_Solid(font, text.c_str(), white);
        text_texture = SDL_CreateTextureFromSurface(renderer, text_surface);
        SDL_FreeSurface(text_surface);
    }
    
}

TextInputSprite::~TextInputSprite() {
    delete boundary;
    delete text_boundary;
    delete message_boundary;
    TTF_CloseFont(font);
    SDL_DestroyTexture(texture);
    SDL_DestroyTexture(message_texture);
    SDL_DestroyTexture(text_texture);
}
