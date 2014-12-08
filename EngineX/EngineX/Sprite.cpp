#include "Sprite.h"
#include "Engine.h"

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

void Sprite::SetX(int x) {
    this->boundary->x = x;
}

void Sprite::SetY(int y) {
    this->boundary->y = y;
}

int Sprite::GetX() {
    return boundary->x;
}

int Sprite::GetY() {
    return boundary->y;
}

void Sprite::HandleEvent(SDL_Event event) {
    for (action_listener listener : action_listeners) {
        if (event.type == SDL_MOUSEMOTION || event.type == SDL_MOUSEBUTTONDOWN || event.type == SDL_MOUSEBUTTONUP || event.type == SDL_MOUSEWHEEL) {
            HandleMouseEvent(event, listener);
        } else if (event.type == Engine::time_event_type) {
            HandleTimeEvent(event, listener);
        } else {
            listener(event);
        }
    }
}

void Sprite::HandleMouseEvent(SDL_Event event, action_listener listener) {
    if (Contains(event.button.x, event.button.y)) {
        listener(event);
    }
}

void Sprite::HandleTimeEvent(SDL_Event event, action_listener listener) {
    std::cout << "Handle time event\n";
}


bool Sprite::Contains(int x, int y) {
    return x >= boundary->x && x <= (boundary->x+boundary->w) && y >= boundary->y && y <= (boundary->y+boundary->h);
}

Sprite::~Sprite() {
    // Destruction of the sprite is handled in the subclasses
}