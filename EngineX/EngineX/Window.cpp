#include "Window.h"
#include "Sprite.h"
#include "ImageSprite.h"

Window::Window(std::string title, int width, int height):title(title), width(width), height(height){
    InitSDL();
    InitSDLImage();
    SetUpWindow();
    SetUpRenderer();
    SDL_RenderPresent(renderer);
}

SDL_Renderer* Window::GetRenderer() {
    return renderer;
}

// Needs to happend in this order due to the fact that the sprite needs access to the renderer...
void Window::AddSprite(Sprite* sprite) {
    sprite->SetRenderer(renderer);
    sprite->SetUpTexture();
    sprites.push_back(sprite);
}

void Window::RemoveSprite(Sprite* sprite) {
    delete sprite;
    for (int i = 0; i < sprites.size(); i++) {
        if (sprite == sprites[i]) {
            sprites.erase(sprites.begin() + i);
        }
    }
}

std::vector<Sprite*> Window::GetSprites() {
    return sprites;
}

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

void Window::PropagateEventToSprites(SDL_Event event) {
    for (Sprite* sprite : sprites) {
        sprite->HandleEvent(event);
    }
}

int Window::GetWidth() {
    return width;
}

int Window::GetHeight() {
    return height;
}

void Window::SetBackground(std::string background_image_path) {
    Sprite* background_sprite = ImageSprite::GetInstance(background_image_path, 0, 0, width , height);
    AddSprite(background_sprite);
}

void Window::InitSDL() { // TODO: throw error to application
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0){
        std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
    }
}

void Window::InitSDLImage() { // TODO: throw error to application
    int img_flags = IMG_INIT_PNG;
    if (!(IMG_Init( img_flags ) & img_flags )) {
        std::cout << "IMG_Init Error: " << IMG_GetError() << std::endl;
        SDL_Quit();
    }
}

void Window::SetUpRenderer() { // TODO: throw error to application
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == nullptr){
        std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
    }
}

void Window::SetUpWindow() { // TODO: throw error to application
    window = SDL_CreateWindow(title.c_str(), 0, 0, width, height, SDL_WINDOW_SHOWN);
    if (window == nullptr){
        std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
    }
}

bool Window::Contains(int x, int y) {
    return x >= 0 && x <= width && y >= 0 && y <= height;
}

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

Window::~Window() {
    for (Sprite* sprite : sprites) {
        delete sprite;
    }
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
}