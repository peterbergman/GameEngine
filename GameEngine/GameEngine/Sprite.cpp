#include <math.h>
#include "Sprite.h"
#include "Engine.h"
#include "Window.h"

Sprite::Sprite(std::string tag, int x_pos, int y_pos, int width, int height, std::string file_name):tag(tag), file_name(file_name), texture(NULL), is_removed(false), is_visible(true) {
    boundary.x = x_pos;
    boundary.y = y_pos;
    boundary.h = height;
    boundary.w = width;
}

// Sets the window member variable.
void Sprite::SetWindow(Window* window) {
    this->window = window;
}

// Adds a new event listener to the interal map that contains all event listeners.
// The keycode is used as key, meaning that two event listeners with the same keycode cannot be
// registered at the same time.
void Sprite::AddEventListener(std::function<void(SDL_Event&, Sprite*)> listener, int key_code) {
    event_listeners[key_code] = listener;
}

// Adds a new time listener to the internal map that contains all time listeners.
// The delay is used as key, meaning that two time listeners with the same delay cannot be
// registered at the same time.
void Sprite::AddTimeListener(std::function<void(Sprite*)> listener, int delay) {
    time_listeners[delay] = listener;
}

// Sets the X value of the upper right coordinate for the sprite.
void Sprite::SetX(int x) {
    boundary.x = x;
}

// Sets the Y value of the upper right coordinate for the sprite.
void Sprite::SetY(int y) {
    boundary.y = y;
}

// Returns the X value of the upper right coordinate for the sprite.
int Sprite::GetX() {
    return boundary.x;
}

// Returns the Y value of the upper right coordinate for the sprite.
int Sprite::GetY() {
    return boundary.y;
}

// Returns the width of the sprite.
int Sprite::GetWidth() {
    return boundary.w;
}

// Returns the height of the sprite.
int Sprite::GetHeight() {
    return boundary.h;
}

// Returns the tag of the sprite.
std::string Sprite::GetTag() {
    return tag;
}

// Sets a flag that indicates that the sprite will be removed.
void Sprite::SetIsRemoved(bool is_removed) {
    this->is_removed = true;
}

// Returns the flag that indicate if the sprite is marked for removal or not.
bool Sprite::GetIsRemoved() {
    return is_removed;
}

// Sets the flag that indicates that the sprite is visible.
void Sprite::SetIsVisible(bool is_visible) {
    this->is_visible = is_visible;
}

// Returns the flag that indicates if the sprite is visible or not.
bool Sprite::GetIsVisible() {
    return is_visible;
}

// Delegates an event to the correct handler.
void Sprite::DelegateEvent(SDL_Event& event) {
    if (event.type == SDL_MOUSEMOTION || event.type == SDL_MOUSEBUTTONDOWN || event.type == SDL_MOUSEBUTTONUP || event.type == SDL_MOUSEWHEEL) {
        HandleEvent(event, true);
    } else if (event.type == Engine::GetTimeEventType()) {
        HandleTime(event);
    } else {
        HandleEvent(event, false);
    }
}

// Iterates through each event listener and evaluates if the event listener should be called.
// This is done by checking that the event source corresponds to the key or button registererd for the listner.
// For mouse events, the position of the mouse coursor is checked if inside the sprite boundary as well before
// calling the event listener.
void Sprite::HandleEvent(SDL_Event& event, bool mouse_event) {
    for (std::pair<const int, std::function<void(SDL_Event&, Sprite*)>>& entry : event_listeners) {
        if (mouse_event && entry.first == event.type) {
            if (Contains(event.button.x, event.button.y)) {
                entry.second(event, this);
            }
        } else if (!mouse_event && entry.first == event.key.keysym.sym) {
            entry.second(event, this);
        } else if (entry.first == event.type) { // Other types of events (text input...)
            entry.second(event, this);
        }
    }
}

// Iterates through each time listener and evaluates if the time listener should be called.
// This is done by calculating the number of main event loop iterations that should elapse before the time event listener is called.
// Example:
// if the current fps is set to 30 and the delay for a time event listener is set to 60. Then that specific time event listener
// should be called every second main event loop iteration.
void Sprite::HandleTime(SDL_Event& event) {
    for (std::pair<const int, std::function<void(Sprite*)>>& entry : time_listeners) {
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
    return x >= boundary.x && x <= (boundary.x + boundary.w) && y >= boundary.y && y <= (boundary.y + boundary.h);
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
    if (file_name != "") {
        if (texture != nullptr) {
            SDL_DestroyTexture(texture);
        }
        SDL_Surface* surface = IMG_Load(file_name.c_str());
        if (surface == nullptr) {
            throw std::runtime_error("Failed to create sprite!");
        } else {
            texture = SDL_CreateTextureFromSurface(window->GetRenderer(), surface);
            SDL_FreeSurface(surface);
            if (texture == nullptr) {
                throw std::runtime_error("Failed to create sprite!");
            }
        }
    }
}

Sprite::~Sprite() {
    SDL_DestroyTexture(texture);
}