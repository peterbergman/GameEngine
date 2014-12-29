#include "Window.h"

Window::Window(std::string title, int width, int height):title(title), width(width), height(height){
    InitSDL();
    InitSDLImage();
    SetUpWindow();
    SetUpRenderer();
    SDL_RenderPresent(renderer);
}

// Returns the renderer used by the window.
SDL_Renderer* Window::GetRenderer() {
    return renderer;
}

// Adds a new sprite to the internal window by taking in a sprite pointer as argument.
// First sends the renderer for the window to the sprite since the sprite needs it in order to draw itself.
// When the sprite has access to the render, it can create its texture. This is done here by calling Sprite::SetUpTexture.
// After these steps, the sprite can be added to the vector of sprites which will be rendererd during the next iteration of the main event loop.
void Window::AddSprite(Sprite* sprite) {
    sprite->SetRenderer(renderer);
    sprite->SetUpTexture();
    sprites.push_back(sprite);
}

// Removes an existing sprite from the window by taking in a sprite pointer as argument.
// Both frees the memory allocated by the sprite object and removes it from the vector of sprites.
void Window::RemoveSprite(Sprite* sprite) {
    delete sprite;
    for (int i = 0; i < sprites.size(); i++) {
        if (sprite == sprites[i]) {
            sprites.erase(sprites.begin() + i);
        }
    }
}

// Returns a vector of all sprites that have been added to the window.
std::vector<Sprite*> Window::GetSprites() {
    return sprites;
}

// Renders all sprites that have been added to the window and that are positioned wihtin the window.
// This is done by iterating through all sprites and calling Sprite::Draw. If a sprite is found that is not within the boundaries of the window,
// then that specific sprite is removed. This includes both freeing the memory allocated by the sprite object
// and removing it from the vector of sprites.
void Window::DrawSprites(int time_elapsed) {
    SDL_RenderClear(renderer);
    for (int i = 0; i < sprites.size(); i++) {
        Sprite* current_sprite = sprites[i];
        if (!Contains(current_sprite)) {
            delete current_sprite;
            sprites.erase(sprites.begin() + i);
        } else {
            current_sprite->Draw(time_elapsed);
        }
    }
    SDL_RenderPresent(renderer);
}

// Delegates an event to the sprites that have been added to the window.
void Window::PropagateEventToSprites(SDL_Event event) {
    for (Sprite* sprite : sprites) {
        sprite->HandleEvent(event);
    }
}

// Returns the width of the window.
int Window::GetWidth() {
    return width;
}

// Returns the height of the window.
int Window::GetHeight() {
    return height;
}

// Sets the background of the window by loading the image located at the the path specified as argument.
// The background is added to the window as a new StaticSprite which is then by calling Window::AddSprite.
// The background is then shown on the screen at the next iteration of the main event loop.
void Window::SetBackground(std::string background_image_path) {
    Sprite* background_sprite = StaticSprite::GetInstance(background_image_path, 0, 0, width , height);
    AddSprite(background_sprite);
}

// Internal helper function to initiate SDL.
void Window::InitSDL() { // TODO: throw error to application
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0){
        std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
    }
}

// Internal helper function to initiate SDL_Image.
void Window::InitSDLImage() { // TODO: throw error to application
    int img_flags = IMG_INIT_PNG;
    if (!(IMG_Init( img_flags ) & img_flags )) {
        std::cout << "IMG_Init Error: " << IMG_GetError() << std::endl;
        SDL_Quit();
    }
}

// Internal helper function to set up a renderer for the window.
void Window::SetUpRenderer() { // TODO: throw error to application
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == nullptr){
        std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
    }
}

// Internal helper function to set up the actual window.
void Window::SetUpWindow() { // TODO: throw error to application
    window = SDL_CreateWindow(title.c_str(), 0, 0, width, height, SDL_WINDOW_SHOWN);
    if (window == nullptr){
        std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
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

// Iterates through all sprites and deletes them.
// Destroys SDL resources and quits the SDL framework.
Window::~Window() {
    for (Sprite* sprite : sprites) {
        delete sprite;
    }
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
}