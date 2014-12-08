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
    sprite->SetUpTexture();
    sprites.push_back(sprite);
}

void Window::DrawSprites() {
    SDL_RenderClear(renderer);
    for (int i = 0; i < sprites.size(); i++) {
        Sprite* current_sprite = sprites[i];
        if (!Contains(current_sprite->GetX(), current_sprite->GetY())) {
            delete current_sprite;
            sprites.erase(sprites.begin()+i);
        } else {
            current_sprite->Draw();
        }
    }
    SDL_RenderPresent(renderer);
}

void Window::PropagateEventToSprites(SDL_Event event) {
    for (Sprite* sprite : sprites) {
        sprite->HandleEvent(event);
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

bool Window::Contains(int x, int y) {
    return x >= 0 && x <= width && y >= 0 && y <= height;
}

Window::~Window() {
    for (Sprite* sprite : sprites) {
        delete sprite;
    }
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
}