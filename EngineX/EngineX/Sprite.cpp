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
    action_event_listeners.push_back(listener);
}

void Sprite::AddTimeEventListener(action_listener listener, int delay) {
    time_event_listeners[delay] = listener;
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
    if (event.type == SDL_MOUSEMOTION || event.type == SDL_MOUSEBUTTONDOWN || event.type == SDL_MOUSEBUTTONUP || event.type == SDL_MOUSEWHEEL) {
        HandleActionEvent(event, true);
    } else if (event.type == Engine::time_event_type) {
        HandleTimeEvent(event);
    } else {
        HandleActionEvent(event, false);
    }
}

void Sprite::HandleActionEvent(SDL_Event event, bool mouse_event) {
    for (action_listener listener : action_event_listeners) {
        if (mouse_event) {
            if (Contains(event.button.x, event.button.y)) {
                listener(event);
            }
        } else {
            listener(event);
        }
    }
}

void Sprite::HandleTimeEvent(SDL_Event event) {
    for (std::pair<const int, action_listener>& entry : time_event_listeners) {
        entry.second(event);
    }
}


bool Sprite::Contains(int x, int y) {
    return x >= boundary->x && x <= (boundary->x+boundary->w) && y >= boundary->y && y <= (boundary->y+boundary->h);
}

Sprite::~Sprite() {
    // Destruction of the sprite is handled in the subclasses
}