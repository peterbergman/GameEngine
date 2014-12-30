#include <math.h>
#include "Sprite.h"
#include "Engine.h"

Sprite::Sprite(int x_pos, int y_pos, int width, int height, std::string file_name):file_name(file_name), texture(NULL) {
    boundary = new SDL_Rect();
    boundary->x = x_pos;
    boundary->y = y_pos;
    boundary->h = height;
    boundary->w = width;
}

void Sprite::SetRenderer(SDL_Renderer* renderer) {
    this->renderer = renderer;
}

void Sprite::AddEventListener(event_listener listener, int key_code) {
    event_listeners[key_code] = listener;
}

void Sprite::AddTimeListener(event_listener listener, int delay) {
    time_listeners[delay] = listener;
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

int Sprite::GetWidth() {
    return boundary->w;
}

int Sprite::GetHeight() {
    return boundary->h;
}

void Sprite::DelegateEvent(SDL_Event event) {
    if (event.type == SDL_MOUSEMOTION || event.type == SDL_MOUSEBUTTONDOWN || event.type == SDL_MOUSEBUTTONUP || event.type == SDL_MOUSEWHEEL) {
        HandleEvent(event, true);
    } else if (event.type == Engine::time_event_type) {
        HandleTime(event);
    } else {
        HandleEvent(event, false);
    }
}

void Sprite::HandleEvent(SDL_Event event, bool mouse_event) {
    for (std::pair<const int, event_listener>& entry : event_listeners) {
        if (mouse_event && entry.first == event.type) {
            if (Contains(event.button.x, event.button.y)) {
                entry.second(this);
            }
        } else if (!mouse_event && entry.first == event.key.keysym.sym) {
            entry.second(this);
        }
    }
}

void Sprite::HandleTime(SDL_Event event) {
    for (std::pair<const int, event_listener>& entry : time_listeners) {
        int fps = *((int*)event.user.data1);
        int frame_counter = *((int*)event.user.data2);
        int rhs = (int)(round(((fps / 1000.0 ) * entry.first)));
        if (rhs > 0) {
            int result = frame_counter % rhs;
            if (result == 0) {
                entry.second(this);
            }
        } else {
            entry.second(this);
        }
    }
}


bool Sprite::Contains(int x, int y) {
    return x >= boundary->x && x <= (boundary->x+boundary->w) && y >= boundary->y && y <= (boundary->y+boundary->h);
}

bool Sprite::Contains(Sprite* other_sprite) {    
    SDL_Point upper_left = {other_sprite->GetX(), other_sprite->GetY()};
    SDL_Point upper_right = {other_sprite->GetX() + other_sprite->GetWidth(), other_sprite->GetY()};
    SDL_Point lower_left = {other_sprite->GetX(), other_sprite->GetY() + other_sprite->GetHeight()};
    SDL_Point lower_right = {other_sprite->GetX() + other_sprite->GetWidth(), other_sprite->GetY() + other_sprite->GetHeight()};
    return Contains(upper_left.x, upper_left.y)
            || Contains(upper_right.x, upper_right.y)
            || Contains(lower_left.x, lower_left.y)
            || Contains(lower_right.x, lower_right.y);
}

void Sprite::SetUpTexture() {
    if (texture != nullptr) {
        SDL_DestroyTexture(texture);
    }
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
    // Destruction of the sprite is handled in the subclasses
}