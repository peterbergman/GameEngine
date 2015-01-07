#include "Level.h"
#include "Window.h"
#include "Engine.h"

Level::Level(int goal):goal(goal), is_loaded(false) {
    
}

// Adds a new sprite to the internal window by taking in a sprite pointer as argument.
// First sends the renderer for the window to the sprite since the sprite needs it in order to draw itself.
// When the sprite has access to the render, it can create its texture. This is done here by calling Sprite::SetUpTexture.
// After these steps, the sprite can be added to the vector of sprites which will be rendererd during the next iteration of the main event loop.
void Level::AddSprite(Sprite* sprite) {
    sprites.push_back(sprite);
    if (is_loaded) {
        window->LoadSprite(sprite);
    }
}

// Removes an existing sprite from the window by taking in a sprite pointer as argument.
// Both frees the memory allocated by the sprite object and removes it from the vector of sprites.
void Level::RemoveSprite(Sprite* sprite) {
    sprite->SetIsRemoved(true);
}

void Level::CleanUpSprites() {
    for (int i = 0; i < sprites.size(); i++) {
        if (sprites[i]->GetIsRemoved()) {
            delete sprites[i];
            sprites.erase(sprites.begin() + i);
        }
    }
}

// Returns a vector of all sprites that have been added to the window.
std::vector<Sprite*> Level::GetSprites() {
    return sprites;
}

// Sets the background of the level by loading the image located at the the path specified as argument.
// The background is added to the level as a new StaticSprite which is then by calling Window::AddSprite.
void Level::SetBackground(std::string background_image_path) {
    Sprite* background_sprite = StaticSprite::GetInstance("background", background_image_path, 0, 0, 0, 0);
    AddSprite(background_sprite);
}

// Sets the loaded flag of this level.
void Level::SetLoaded(bool is_loaded) {
    this->is_loaded = is_loaded;
}

// Returns the goal for this level.
int Level::GetGoal() {
    return goal;
}

// Sets the window pointer needed to load more sprites is new ones are added after the level is loaded.
void Level::SetWindow(Window* window) {
    this->window = window;
}

// Adds a new time listener to the internal map that contains all time listeners.
// The delay is used as key, meaning that two time listeners with the same delay cannot be
// registered at the same time.
void Level::AddTimeListener(std::function<void(void)> listener, int delay) {
    time_listeners[delay] = listener;
}

// Delegates an event to the sprites that have been added to the level and the time listeners added to the level.
void Level::DelegateEvent(SDL_Event& event) {
    if (event.type == Engine::GetTimeEventType()) {
        HandleTime(event);
    }
    for (Sprite* sprite : sprites) {
        sprite->DelegateEvent(event);
    }
}

// Iterates through each time listener and evaluates if the time listener should be called.
// This is done by calculating the number of main event loop iterations that should elapse before the time event listener is called.
// Example:
// if the current fps is set to 30 and the delay for a time event listener is set to 60. Then that specific time event listener
// should be called every second main event loop iteration.
void Level::HandleTime(SDL_Event& event) {
    for (std::pair<const int, std::function<void(void)>>& entry : time_listeners) {
        int fps = *((int*)event.user.data1);
        int frame_counter = *((int*)event.user.data2);
        int rhs = (int)(round(((fps / 1000.0 ) * entry.first)));
        if (rhs > 0) {
            int result = frame_counter % rhs;
            if (result == 0) {
                entry.second();
            }
        } else {
            entry.second();
        }
    }
}

Level::~Level() {
    for (Sprite* sprite : sprites) {
        delete sprite;
    }
}