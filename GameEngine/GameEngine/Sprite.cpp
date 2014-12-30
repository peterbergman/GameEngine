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

// Sets the renderer member variable.
void Sprite::SetRenderer(SDL_Renderer* renderer) {
    this->renderer = renderer;
}

// Adds a new event listener to the interal map that contains all event listeners.
// The keycode is used as key, meaning that two event listeners with the same keycode cannot be
// registered at the same time.
void Sprite::AddEventListener(event_listener listener, int key_code) {
    event_listeners[key_code] = listener;
}

// Adds a new time listener to the internal map that contains all time listeners.
// The delay is used as key, meaning that two time listeners with the same delay cannot be
// registered at the same time.
void Sprite::AddTimeListener(event_listener listener, int delay) {
    time_listeners[delay] = listener;
}

// Sets the X value of the upper right coordinate for the sprite.
void Sprite::SetX(int x) {
    this->boundary->x = x;
}

// Sets the Y value of the upper right coordinate for the sprite.
void Sprite::SetY(int y) {
    this->boundary->y = y;
}

// Returns the X value of the upper right coordinate for the sprite.
int Sprite::GetX() {
    return boundary->x;
}

// Returns the Y value of the upper right coordinate for the sprite.
int Sprite::GetY() {
    return boundary->y;
}

// Returns the width of the sprite.
int Sprite::GetWidth() {
    return boundary->w;
}

// Returns the height of the sprite.
int Sprite::GetHeight() {
    return boundary->h;
}

// Delegates an event to the correct handler.
void Sprite::DelegateEvent(SDL_Event event) {
    if (event.type == SDL_MOUSEMOTION || event.type == SDL_MOUSEBUTTONDOWN || event.type == SDL_MOUSEBUTTONUP || event.type == SDL_MOUSEWHEEL) {
        HandleEvent(event, true);
    } else if (event.type == Engine::time_event_type) {
        HandleTime(event);
    } else {
        HandleEvent(event, false);
    }
}

// Iterates through each event listener and evaluates if the event listener should be called.
// This is done by checking that the event source corresponds to the key or button registererd for the listner.
// For mouse events, the position of the mouse coursor is checked if inside the sprite boundary as well before
// calling the event listener.
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

// Iterates through each time listener and evaluates if the time listener should be called.
// This is done by calculating the number of main event loop iterations that should elapse before the time event listener is called.
// Example:
// if the current fps is set to 30 and the delay for a time event listener is set to 60. Then that specific time event listener
// should be called every second main event loop iteration.
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

// Checks if any given x and y value are within the bounds of the sprite.
bool Sprite::Contains(int x, int y) {
    return x >= boundary->x && x <= (boundary->x+boundary->w) && y >= boundary->y && y <= (boundary->y+boundary->h);
}

// Checks if any given sprite is within the bounds of this sprite.
// For this to return false, all four corners of the other sprite needs to be outside of the
// bounds of this sprite.
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

// Sets up the texture and loads the image used by the sprite.
// If a texture is already present when this function is called, then that texture is first destroyed.
// This is to enable change of texture after the sprite is created without leaking memory.
void Sprite::SetUpTexture() {
    if (texture != nullptr) {
        SDL_DestroyTexture(texture);
    }
    SDL_Surface* surface = IMG_Load(file_name.c_str());
    if (surface == nullptr) {
        throw std::runtime_error("Failed to create sprite!");
    } else {
        texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_FreeSurface(surface);
        if (texture == nullptr) {
            throw std::runtime_error("Failed to create sprite!");
        }
    }
}

// Destruction of the sprite is handled in the subclasses so this destructor
// is intentionally leaved empty.
Sprite::~Sprite() {
    
}