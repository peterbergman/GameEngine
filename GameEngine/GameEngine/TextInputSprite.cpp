#include "TextInputSprite.h"
#include "Window.h"

TextInputSprite* TextInputSprite::GetInstance(std::string tag, int x_pos, int y_pos) {
    return new TextInputSprite(tag, x_pos, y_pos);
}

TextInputSprite::TextInputSprite(std::string tag, int x_pos, int y_pos):Sprite(tag, x_pos, y_pos, 12, 50, "") {
    std::function<void(SDL_Event&, Sprite*)> text_input_handler_function = std::bind(&TextInputSprite::HandleTextInput, this, std::placeholders::_1);
    AddEventListener(text_input_handler_function, SDL_TEXTINPUT);
}

// Returns the current text entered.
std::string TextInputSprite::GetText() {
    return text;
}

void TextInputSprite::Draw(int time_elapsed) {
    SDL_RenderCopy(window->GetRenderer(), texture, NULL, &boundary);
}

void TextInputSprite::HandleTextInput(SDL_Event& event) {
    boundary.w = boundary.w  + 25;
    boundary.x = boundary.x - 12;
    
    text += event.text.text;
    
    if (window->GetRenderer() != nullptr) {
        SDL_Color white = { 255, 255, 255 };
        SDL_DestroyTexture(texture);
        SDL_Surface* text_surface = TTF_RenderText_Solid(window->GetFont(), text.c_str(), white);
        texture = SDL_CreateTextureFromSurface(window->GetRenderer(), text_surface);
        SDL_FreeSurface(text_surface);
    }
    
}

TextInputSprite::~TextInputSprite() {
}
