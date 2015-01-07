#include <SDL2/SDL.h>
#include <SDL2_ttf/SDL_ttf.h>
#include "Window.h"
#include "Level.h"

Window::Window(std::string title, int width, int height):title(title), width(width), height(height){
    InitSDL();
    InitSDLImage();
    InitSDLttf();
    SetUpWindow();
    SetUpRenderer();
    SDL_RenderPresent(renderer);
}

// Returns the renderer used by the window.
SDL_Renderer* Window::GetRenderer() {
    return renderer;
}

// Iterates through all sprites in the specified level and loads them.
void Window::LoadLevel(Level* level) {
    for (int i = 0; i < level->GetSprites().size(); i++) {
        LoadSprite(level->GetSprites()[i]);
    }
    level->SetLoaded(true);
    level->SetWindow(this);
    current_level = level;
}

// Sends the renderer to a sprite and sets up the texture for the sprite.
void Window::LoadSprite(Sprite* sprite) {
    sprite->SetRenderer(renderer);
    sprite->SetUpTexture();
}

// Renders all sprites that have been added to the level that is currently loaded and that are positioned wihtin the window.
// This is done by iterating through all sprites and calling Sprite::Draw. If a sprite is found that is not within the boundaries of the window,
// then that specific sprite is removed. This includes both freeing the memory allocated by the sprite object
// and removing it from the vector of sprites.
void Window::DrawSprites(int time_elapsed) {
    SDL_RenderClear(renderer);
    for (int i = 0; i < current_level->GetSprites().size(); i++) {
        Sprite* current_sprite = current_level->GetSprites()[i];
        if (!Contains(current_sprite)) {
            current_level->RemoveSprite(current_sprite); // TODO: add remove(index) to avoid duplicate iteration
        } else {
            if (current_sprite->GetIsVisible()) {
                current_sprite->Draw(time_elapsed);
            }
        }
    }
    SDL_RenderPresent(renderer);
}

// Returns the width of the window.
int Window::GetWidth() {
    return width;
}

// Returns the height of the window.
int Window::GetHeight() {
    return height;
}

// Internal helper function to initiate SDL.
void Window::InitSDL() {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0){
        throw std::runtime_error("Failed to init game engine!");
    }
}

// Internal helper function to initiate SDL_Image.
void Window::InitSDLImage() {
    int img_flags = IMG_INIT_PNG;
    if (!(IMG_Init( img_flags ) & img_flags )) {
        SDL_Quit();
        throw std::runtime_error("Failed to init game engine!");
    }
}

// Internal helper function to initiate SDL_ttf.
void Window::InitSDLttf() {
    if (TTF_Init() == -1) {
        SDL_Quit();
        throw std::runtime_error("Failed to init game engine!");
    }
}

// Internal helper function to set up a renderer for the window.
void Window::SetUpRenderer() {
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == nullptr){
        SDL_DestroyWindow(window);
        SDL_Quit();
        throw std::runtime_error("Failed to init game engine!");
    } else {
        SDL_RenderClear(renderer);
    }
}

// Internal helper function to set up the actual window.
void Window::SetUpWindow() {
    window = SDL_CreateWindow(title.c_str(), 0, 0, width, height, SDL_WINDOW_SHOWN);
    if (window == nullptr){
        SDL_Quit();
        throw std::runtime_error("Failed to init game engine!");
    }
}

// Checks if any given x and y value are within the bounds of the window.
bool Window::Contains(int x, int y) {
    return x >= 0 && x <= width && y >= 0 && y <= height;
}

// Checks if any given sprite is within the bounds of the window.
// For this to return false, all four corners of the sprite needs to be outside of the
// bounds of the window.
bool Window::Contains(Sprite* sprite) {
    SDL_Point sprite_upper_left = {sprite->GetX(), sprite->GetY()};
    SDL_Point sprite_upper_right = {sprite->GetX() + sprite->GetWidth(), sprite->GetY()};
    SDL_Point sprite_lower_left = {sprite->GetX(), sprite->GetY() + sprite->GetHeight()};
    SDL_Point sprite_lower_right = {sprite->GetX() + sprite->GetWidth(), sprite->GetY() + sprite->GetHeight()};
    return Contains(sprite_upper_left.x, sprite_upper_left.y)
            || Contains(sprite_upper_right.x, sprite_upper_right.y)
            || Contains(sprite_lower_left.x, sprite_lower_left.y)
            || Contains(sprite_lower_right.x, sprite_lower_right.y);
    
}

// Destroys SDL resources and quits the SDL framework.
Window::~Window() {
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    //TTF_Quit();
}