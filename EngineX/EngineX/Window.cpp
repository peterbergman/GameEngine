#include "Window.h"
#include "Sprite.h"

Window::Window(std::string title, int height, int width):title(title), height(height), width(width){
    InitSDL();
    InitSDLImage();
    SetUpWindow();
    SetUpRenderer();
    SDL_RenderPresent(renderer);
}

SDL_Renderer* Window::GetRenderer() {
    return renderer;
}

void Window::AddSprite(Sprite* sprite) {
    sprite->SetRenderer(renderer);
    sprites.push_back(sprite);
}

void Window::DrawSprites() {
    for (Sprite* sprite : sprites) {
        sprite->Draw();
    }
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

Window::~Window() {
    for (Sprite* sprite : sprites) {
        delete sprite;
    }
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
}