#include "Sprite.h"
Sprite::Sprite(int x_pos, int y_pos, int height, int width) {
    boundary = new SDL_Rect();
    boundary->x = x_pos;
    boundary->y = y_pos;
    boundary->h = height;
    boundary->w = width;
}

void Sprite::SetRenderer(SDL_Renderer* renderer) {
    this->renderer = renderer;
}

void Sprite::AddActionListener(action_listener listener) {
    action_listeners.push_back(listener);
}

void Sprite::HandleEvent(ActionEvent event) {
    for (action_listener listener : action_listeners) {
        listener(event);
    }
}

Sprite::~Sprite() {
    // Destruction of the sprite is handled in the subclasses
}